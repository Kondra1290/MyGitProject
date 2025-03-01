%define _unpackaged_files_terminate_build 1

Name:    Kondrashov_rpmbuild_ASCCIGraphic
Version: 1.0
Release: alt1
Summary: Most simple RPM package
License: no
Group:   Development/Other
Source:  %name-%version.tar
BuildRequires: gcc-c++

%description
This is my first RPM

%prep
%setup -n %name

%build
%make_build Kondrashov_rpmbuild_ASCCIGraphic

%install
mkdir -p %{buildroot}%_bindir
install -m 755 Kondrashov_rpmbuild_ASCCIGraphic %{buildroot}%_bindir

%files
%_bindir/%name

%changelog
* Mon Apr 01 2024 Some One <someone@altlinux.org> 1.0-alt1
- Init Build
