/* This file is Copyright 2000-2009 Meyer Sound Laboratories Inc.  See the included LICENSE.txt file for details. */

#ifndef MuscleQSocketDataIO_h
#define MuscleQSocketDataIO_h

#include <QtNetwork/QUdpSocket>
#include "dataio/DataIO.h"

namespace muscle {

/** This class was contributed to the MUSCLE archive by Jonathon Padfield
  * (jpadfield@hotkey.net.au).  It's a good alternative to the QMessageTransceiverThread
  * class if you don't want to use the multi-threaded version of Qt.
  *
  * The QSocket object emits signals whenever it receives data, which you
  * can connect to your Muscle client. eg.
  *
  *  connect(muscleSocket, SIGNAL(hostFound()), SLOT(slotHostFound()));
  *  connect(muscleSocket, SIGNAL(connected()), SLOT(slotConnected()));
  *  connect(muscleSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
  *  connect(muscleSocket, SIGNAL(bytesWritten(int)), SLOT(slotBytesWritten(int)));
  *
  * You can then use the normal QSocket routines to connect to the server
  * while running all the input through the MessageIO interface.
  *
  * @author Jonathon Padfield
  */
class QUDPSocketDataIO : public DataIO
{
public:
   /** Class constructor.
    *  @param newSocket a QSocket object that was allocated off the heap.  This object becomes owner of newSocket.
    */
   QUDPSocketDataIO(QUdpSocket *newSocket) : _socket(newSocket) {/* empty */}

   /** Destructor - deletes the held QSocket (if any) */
   virtual ~QUDPSocketDataIO() {Shutdown();}

   /** Reads up to (size) bytes of new data from the QSocket into (buffer).
    *  Returns the actual number of bytes placed, or a negative value if there
    *  was an error.
    *  @param buffer Buffer to write the bytes into
    *  @param size Number of bytes in the buffer.
    *  @return Number of bytes read, or -1 on error.
    */
   virtual int32 Read(void * buffer, uint32 size) {
	   //uint32 gotSize = _socket->pendingDatagramSize();
	   //size = gotSize;
	   QByteArray datagram;
	   datagram.resize(size);
	   char *buf = (char *)malloc(10);
	   qint64 ret = _socket->readDatagram((char *)buf, size, &address, &port);
		   if (ret == -1) {
			  return -1;
		  } else {
			  buffer = buf;
			  return ret;
		  }
   };

   /** Takes (size) bytes from (buffer) and pushes them in to the
    *  outgoing I/O stream of the QSocket.  Returns the actual number of bytes
    *  read from (buffer) and pushed, or a negative value if there
    *  was an error.
    *  @param buffer Buffer to read the bytes from.
    *  @param size Number of bytes in the buffer.
    *  @return Number of bytes written, or -1 on error.
    */
#ifdef WIN32
   #pragma warning( disable : 4100 )
#endif
   virtual int32 Write(const void * buffer, uint32 size) {return -1;}
#ifdef WIN32
   #pragma warning( default : 4100 )
#endif

   /**
    * Always returns B_ERROR (you can't seek a QSocket!)
    */
   virtual status_t Seek(int64 /*offset*/, int /*whence*/) {return B_ERROR;}

   /** Always returns -1, since a socket has no position to speak of */
   virtual int64 GetPosition() const {return -1;}

   /**
    * Flushes the output buffer, if possible.
    */
   virtual void FlushOutput() {if (_socket) _socket->flush();}

   /**
    * Closes the connection.  After calling this method, the
    * DataIO object should not be used any more.
    */
   virtual void Shutdown() {if (_socket) _socket->disconnectFromHost(); delete _socket; _socket = NULL;}

   /** Returns the fd of our QSocket, if any. */
   virtual const ConstSocketRef & GetSelectSocket() const {return GetNullSocket();}

   /**
    * Returns the held QSocket object (in case you need to access it directly for some reason)
    */
   QUdpSocket * GetSocket() {return _socket;}

   /**
    * Releases the held QSocket object into your custody.  After calling this, this
    * QSocketDataIObject no longer has anything to do with the QSocket object and
    * it becomes your responsibility to delete the QSocket.
    */
   void ReleaseSocket() {_socket = NULL;}

   const QHostAddress getAddress() const { return address;};
   const quint16 getPort() const { return port;};

private:
   QUdpSocket * _socket;
   QHostAddress address;
   quint16 port;
};

class QTCPSocketDataIO : public DataIO
{
public:
   /** Class constructor.
    *  @param newSocket a QSocket object that was allocated off the heap.  This object becomes owner of newSocket.
    */
   QTCPSocketDataIO(QTcpSocket * newSocket) : _socket(newSocket), _socketRef(newSocket?GetConstSocketRefFromPool(newSocket->socketDescriptor(), false):ConstSocketRef()) {/* empty */}

   /** Destructor - deletes the held QSocket (if any) */
   virtual ~QTCPSocketDataIO() {Shutdown();}

   /** Reads up to (size) bytes of new data from the QSocket into (buffer).
    *  Returns the actual number of bytes placed, or a negative value if there
    *  was an error.
    *  @param buffer Buffer to write the bytes into
    *  @param size Number of bytes in the buffer.
    *  @return Number of bytes read, or -1 on error.
    */
   virtual int32 Read(void * buffer, uint32 size) {return _socket ? _socket->read((char *) buffer, size) : -1;}

   /** Takes (size) bytes from (buffer) and pushes them in to the
    *  outgoing I/O stream of the QSocket.  Returns the actual number of bytes
    *  read from (buffer) and pushed, or a negative value if there
    *  was an error.
    *  @param buffer Buffer to read the bytes from.
    *  @param size Number of bytes in the buffer.
    *  @return Number of bytes written, or -1 on error.
    */
   virtual int32 Write(const void * buffer, uint32 size) {return _socket ? _socket->write((char *) buffer, size) : -1;}

   /**
    * Always returns B_ERROR (you can't seek a QSocket!)
    */
   virtual status_t Seek(int64 /*offset*/, int /*whence*/) {return B_ERROR;}

   /** Always returns -1, since a socket has no position to speak of */
   virtual int64 GetPosition() const {return -1;}

   /**
    * Flushes the output buffer, if possible.
    */
   virtual void FlushOutput() {if (_socket) _socket->flush();}

   /**
    * Closes the connection.  After calling this method, the
    * DataIO object should not be used any more.
    */
   virtual void Shutdown() {if (_socket) _socket->disconnectFromHost(); delete _socket; _socket = NULL; _socketRef.Reset();}

   /** Returns the fd of our QSocket, if any. */
   virtual const ConstSocketRef & GetSelectSocket() const {return _socket ? _socketRef : GetNullSocket();}

   /**
    * Returns the held QSocket object (in case you need to access it directly for some reason)
    */
   QTcpSocket * GetSocket() {return _socket;}

   /**
    * Releases the held QSocket object into your custody.  After calling this, this
    * QSocketDataIObject no longer has anything to do with the QSocket object and
    * it becomes your responsibility to delete the QSocket.
    */
   void ReleaseSocket() {_socket = NULL; _socketRef.Neutralize();}

private:
   ConstSocketRef _socketRef;
   QTcpSocket * _socket;
};


}; // end namespace muscle

#endif
