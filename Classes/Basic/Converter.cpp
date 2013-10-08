#include "Converter.h"


string CConverter::U2G( const char* utf8 )
{
#ifdef WIN32
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	std::string strTemp = str;
	return strTemp;
#else
	// if(utf8==0 || strlen(utf8)) return "";

	int iLen = strlen(utf8);	
	char* lpStr=new char[iLen+1];
	Code_Convert("UTF-8","GBK",utf8,iLen,lpStr,iLen+1);
	std::string str = lpStr;
	delete[] lpStr;
	return str;
#endif
}

string CConverter::G2U( const char* gb2312 )
{
#ifdef WIN32
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len,NULL, NULL);
	if(wstr) delete[] wstr;
	std::string strTemp = str;
	return strTemp;
#else
	// gbk µ½ utf-8
	int iLen = strlen(gb2312);
	char* lpStr=new char[(iLen+1)*3];
	Code_Convert("GBK","UTF-8",gb2312,iLen,lpStr,(iLen+1)*3);
	std::string str = lpStr;

	delete[] lpStr;
	return str;
#endif
}
