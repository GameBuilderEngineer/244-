#include "Base.h"
char rootPath[1124]={0};

void initializeDirectory(char* root)
{
	strcpy(rootPath, root);//パス(root)をrootPathへコピー
}

void setRootDirectory()
{
	SetCurrentDirectory(rootPath);
}

void setDataDirectory()
{
	char tmporary[512] = { 0 };
	strcpy(tmporary, rootPath);
	strcat(tmporary, "\\01 Data File");
	SetCurrentDirectory(tmporary);
}

void setVisualDirectory()
{
	char tmporary[512] = { 0 };
	strcpy(tmporary, rootPath);
	strcat(tmporary, "\\02 Visual File");
	SetCurrentDirectory(tmporary);
}

void setShaderDirectory()
{
	char tmporary[512] = { 0 };
	strcpy(tmporary, rootPath);
	strcat(tmporary, "\\03 Shader File");
	SetCurrentDirectory(tmporary);
}

void setSoundDirectory()
{
	char tmporary[512] = { 0 };
	strcpy(tmporary, rootPath);
	strcat(tmporary, "\\04 Sound File");
	SetCurrentDirectory(tmporary);
}
