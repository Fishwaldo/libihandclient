%if %{defined mdkversion}
%define __libtoolize    /bin/true
%endif


Name: libihanclient
Group: Productivity/Networking/Other
Summary: Intelegent Home Automation Network Client Library
URL: http://wiki.my-ho.st/confluence/display/HTC/
License: LGPL2+
Version: 0.1
Release: 1
BuildRequires: gcc-c++ make boost-devel pkgconfig
Source0: libihanclient-%{version}.tar.gz

BuildRoot: %{_tmppath}/%{name}-root

%description
Intelegent Home Automation Network (iHan) Client Library is for application 
developers to write iHan applications

%package -n %{name}-devel
Summary: Intelegent Home Automation Network Client Library
Group: Development/Libraries/C and C++
Requires: %{name} = %{version}-%{release}
#BuildRequires: %{name}

%description -n %{name}-devel
header files needed when you want to compile your own application using 
libihanclient.
Intelegent Home Automation Network (iHan) Client Library is for application 
developers to write iHan applications


%prep

%setup -q
if [ ! -f configure ]; then
	./bootstrap.sh
fi

%build
touch .hush
%configure --disable-static
make %{?_smp_mflags}

%check
make check

%install
make install DESTDIR=${RPM_BUILD_ROOT} 
rm %{buildroot}/usr/bin/demo

%files
%defattr(-,root,root,-)
#%{_prefix}/bin/anetd
%{_libdir}/libihanclient.so.*
#%dir %{_prefix}/include/anetd/
#%dir %{_prefix}/share/doc/libanetd-%{version}/
#%doc %{_prefix}/share/doc/libanetd-%{version}/
%doc README

%files -n %{name}-devel
%defattr(-,root,root,-)
%{_includedir}/libihanclient/*
%{_libdir}/libihanclient.la
%{_libdir}/libihanclient.so
%{_libdir}/pkgconfig/*.pc


%post
/sbin/ldconfig

%postun
/sbin/ldconfig

%changelog
