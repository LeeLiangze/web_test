#pragma once

class WptStatus;

class BrowserInfo {
public:
  BrowserInfo(void){}
  BrowserInfo(const BrowserInfo& src){ *this = src; }
  ~BrowserInfo(void){}
  const BrowserInfo& operator =(const BrowserInfo& src) {
    _installer = src._installer;
    _exe = src._exe;
    _name = src._name;
    return src;
  }
  
  CString _name;
  CString _installer;
  CString _exe;
};

class SoftwareUpdate
{
public:
  SoftwareUpdate(WptStatus &status);
  ~SoftwareUpdate(void);
  void LoadSettings(CString settings_ini);
  bool UpdateSoftware(bool force = false);
  bool ReInstallBrowser(CString browser);
  CString GetUpdateInfo(CString url);
  void SetSoftwareUrl(CString url);
  void SetServerUrl(CString url);
  bool CheckBrowsers(CString& missing_browser);

  CString _ec2_instance;
  CString _ec2_availability_zone;

protected:
  CAtlList<BrowserInfo> _browsers;
  CString           _directory;
  LARGE_INTEGER     _last_update_check;
  LARGE_INTEGER     _perf_frequency_minutes;
  WptStatus         &_status;
  CString           _software_url;
  CString           _server_url;
  CString           _version;
  CString           _build;

  bool UpdateBrowsers(void);
  bool InstallSoftware(CString browser, CString file_url, CString md5,
           CString version, CString command, CString check_file);
  bool TimeToCheck(void);
  bool GetChromeSymbols(CString exe);
  bool FetchChromeSymbols(CString pdb_signature, CString symbols_file);
};

