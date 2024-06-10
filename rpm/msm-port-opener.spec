Name:       msm-port-opener
Version:    1
Release:    0
Summary:    Tool for Qualcomm modem port configuration
License:    MIT
Source:     %{name}-%{version}.tar.gz

BuildRequires:  qrtr-devel

%description
msm-port-opener is a tool which runs at startup and requests
the modem to open a bam-dmux data port which can be used by ofono.

%prep
%setup -q -n %{name}-%{version}

%build
gcc msm-port-opener.c qmi_dpm.c -o msm-port-opener -lqrtr

%install
install -Dm755 msm-port-opener -t %{buildroot}%{_sbindir}
install -Dm644 msm-port-opener.service -t %{buildroot}%{_unitdir}
mkdir -p %{buildroot}%{_unitdir}/multi-user.target.wants
ln -s ../msm-port-opener.service %{buildroot}%{_unitdir}/multi-user.target.wants/msm-port-opener.service

%files
%license LICENSE
%{_sbindir}/msm-port-opener
%{_unitdir}/msm-port-opener.service
%{_unitdir}/multi-user.target.wants/msm-port-opener.service

