/* This file is Copyright 2000-2013 Meyer Sound Laboratories Inc.  See the included LICENSE.txt file for details. */ 

#ifndef MuscleAtomicCounter_h 
#define MuscleAtomicCounter_h 

#include "support/MuscleSupport.h"

#if defined(QT_CORE_LIB)
# include <QtCore>      // for the QT_VERSION number
# include <QAtomicInt>  // Qt4 Atomic counter API, available in Qt 4.4.0 and higher
#endif

#ifndef MUSCLE_SINGLE_THREAD_ONLY
# if defined(__ATHEOS__)
#  include <atheos/atomic.h>
# elif defined(__BEOS__) || defined(__HAIKU__)
#  include <kernel/OS.h>
# elif defined(WIN32)
   // empty
# elif defined(__APPLE__)
#  include <libkern/OSAtomic.h>
# elif defined(MUSCLE_USE_POWERPC_INLINE_ASSEMBLY) || defined(MUSCLE_USE_X86_INLINE_ASSEMBLY)
   // empty
# elif defined(QT_VERSION) && (QT_VERSION >= 0x40400)
#  define MUSCLE_USE_QT_FOR_ATOMIC_OPERATIONS
# elif defined(MUSCLE_USE_PTHREADS) || defined(QT_THREAD_SUPPORT)
#  define MUSCLE_USE_MUTEXES_FOR_ATOMIC_OPERATIONS 1
namespace muscle {
   extern int32 DoMutexAtomicIncrement(volatile int32 * count, int32 delta);
}; // end namespace muscle
# endif
#endif

namespace muscle {

/** This is a teensy little class that works as a cross-platform atomic counter variable. 
  * It's been ifdef'd all to hell, so that it tries to always use the most efficient API
  * possible based on the host CPU and OS.  If compiled with -DMUSCLE_SINGLE_THREAD_ONLY,
  * it degenerates to a regular old counter variable, which is very lightweight and portable,
  * but of course will only work properly in single-threaded environments.
  */
class MUSCLE_EXPORT AtomicCounter
{
public:
   /** Default constructor.  The count value is initialized to zero. */
   AtomicCounter() : _count(0)
   {
      // empty
   }

   /** Destructor */
   ~AtomicCounter()
   {
      // empty
   }

   /** Atomically increments our counter by one. */
   inline void AtomicIncrement() 
   {
#if defined(MUSCLE_SINGLE_THREAD_ONLY) 
      ++_count;
#elif defined(WIN32) 
# if defined(_MSC_VER) && defined(MUSCLE_USE_X86_INLINE_ASSEMBLY)
      volatile int * p = &_count;
      __asm {
              mov eax, p;
              lock inc DWORD PTR [eax];
      };
# else
      (void) InterlockedIncrement(&_count);
# endif
#elif defined(__APPLE__) 
      (void) OSAtomicIncrement32Barrier(&_count);
#elif defined(__ATHEOS__) 
      (void) atomic_add(&_count,1);
#elif defined(__BEOS__) || defined(__HAIKU__)
      (void) atomic_add(&_count,1);
#elif defined(MUSCLE_USE_POWERPC_INLINE_ASSEMBLY)
      volatile int * p = &_count;
      int tmp;  // tmp will be set to the value after the increment
      asm volatile( 
         "1:     lwarx   %0,0,%1\n" 
         "       addic   %0,%0,1\n" 
         "       stwcx.  %0,0,%1\n" 
         "       bne-    1b" 
         : "=&r" (tmp) 
         : "r" (p) 
         : "cc", "memory");
#elif defined(MUSCLE_USE_X86_INLINE_ASSEMBLY)
      volatile int * p = &_count;
      asm volatile(
         "lock; incl (%0)"
         : // No outputs
         : "q" (p)
         : "cc", "memory");
#elif defined(MUSCLE_USE_QT_FOR_ATOMIC_OPERATIONS)
      (void) _count.ref();
#elif defined(MUSCLE_USE_MUTEXES_FOR_ATOMIC_OPERATIONS)
      (void) DoMutexAtomicIncrement(&_count, 1);
#else
# error "No atomic increment supplied for this OS!  Add it here in AtomicCount.h, or put -DMUSCLE_SINGLE_THREAD_ONLY in your Makefile if you will not be using multithreading." 
#endif 
   }

   /** Atomically decrements our counter by one.
     * @returns true iff the new value of our count is zero, or false if it is any other value
     */
   inline bool AtomicDecrement() 
   {
#if defined(MUSCLE_SINGLE_THREAD_ONLY) 
      return (--_count == 0);
#elif defined(WIN32) 
# if defined(_MSC_VER) && defined(MUSCLE_USE_X86_INLINE_ASSEMBLY)
      bool isZero;
      volatile int * p = &_count;
      __asm {
         mov eax, p;
         lock dec DWORD PTR [eax];
         sete isZero;
      };
      return isZero;
# else
      return (InterlockedDecrement(&_count) == 0);
# endif
#elif defined(__APPLE__)
      return (OSAtomicDecrement32Barrier(&_count) == 0);
#elif defined(__ATHEOS__) 
      return (atomic_add(&_count,-1)==1);
#elif defined(__BEOS__) || defined(__HAIKU__)
      return (atomic_add(&_count,-1)==1);
#elif defined(MUSCLE_USE_POWERPC_INLINE_ASSEMBLY)
      volatile int * p = &_count;
      int tmp;   // tmp will be set to the value after the decrement
      asm volatile( 
         "1:     lwarx   %0,0,%1\n" 
         "       addic   %0,%0,-1\n"  // addic allows r0, addi doesn't 
         "       stwcx.  %0,0,%1\n" 
         "       bne-    1b" 
         : "=&r" (tmp) 
         : "r" (p) 
         : "cc", "memory"); 
      return(tmp == 0); 
#elif defined(MUSCLE_USE_X86_INLINE_ASSEMBLY)
      bool isZero;
      volatile int * p = &_count;
      asm volatile(
         "lock; decl (%1)\n"
         "sete %0"
         : "=q" (isZero)
         : "q" (p)
         : "cc", "memory"
         );
      return isZero;
#elif defined(MUSCLE_USE_QT_FOR_ATOMIC_OPERATIONS)
      return (_count.deref() == false);
#elif defined(MUSCLE_USE_MUTEXES_FOR_ATOMIC_OPERATIONS)
      return (DoMutexAtomicIncrement(&_count, -1) == 0);
#else
# error "No atomic decrement supplied for this OS!  Add your own here in AtomicCounter.h, or put -DMUSCLE_SINGLE_THREAD_ONLY in your Makefile if you will not be using multithreading." 
#endif 
   }

   /** Returns the current value of this counter.
     * Be careful when using this function in multithreaded
     * environments, it can easily lead to race conditions
     * if you don't know what you are doing!
     */
   int32 GetCount() const {return (int32) _count;}

   /** Sets the current value of this counter.
     * Be careful when using this function in multithreaded
     * environments, it can easily lead to race conditions
     * if you don't know what you are doing!
     */
   void SetCount(int32 c) {_count = c;}

private:
#if defined(MUSCLE_SINGLE_THREAD_ONLY)
   int32 _count;
#elif defined(__ATHEOS__)
   atomic_t _count;
#elif defined(WIN32)
# if defined(_MSC_VER) && defined(MUSCLE_USE_X86_INLINE_ASSEMBLY)
   volatile int _count;
# else
   long _count;
# endif
#elif defined(__APPLE__)
   volatile int32_t _count;
#elif defined(__BEOS__) || defined(__HAIKU__)
# if defined(B_BEOS_VERSION_5)
   vint32 _count;
# else
   int32 _count;
# endif
#elif defined(MUSCLE_USE_POWERPC_INLINE_ASSEMBLY) || defined(MUSCLE_USE_X86_INLINE_ASSEMBLY)
   volatile int _count;
#elif defined(MUSCLE_USE_QT_FOR_ATOMIC_OPERATIONS)
   QAtomicInt _count;
#else
   volatile int32 _count;
#endif
};

}; // end namespace muscle

#endif
