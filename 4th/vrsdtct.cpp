#include <stdio.h>
#include <string.h>
#include <windows.h>
bool scan_virus(const char *FileName,long offset, int length, void *signature);
void main()
{	WIN32_FIND_DATA stFindFile;
	HANDLE hFindFile;
	char *szFilter = "*.exe";   // 保存搜索的筛选条件（所有exe文件）
	char szFindFile[MAX_PATH];  // 保存欲检测的程序的路径
	char szSearch[MAX_PATH];    // 保存完整筛选路径
	int ret = 0;                // 搜索的返回值
  lstrcpy(szFindFile,"C:\\");
  lstrcpy(szSearch,"C:\\");
	lstrcat(szSearch, szFilter);
	hFindFile = FindFirstFile(szSearch, &stFindFile);
  bool flag=false;
  char input[10];
  char yes[10]='yes';
  char no[10]='no';
  unsigned char signature[]=
  {0x8B,0xF4,0x6A,0x78,0x8D,0x4D,0x80,0x51,0x6A,0x03,0x6A,0x00,0x68,0x40,0x50,0x42,
   0x00,0x8B,0x55,0xFC,0x52,0xFF,0x15,0xD0,0xB1,0x42,0x00,0x3B,0xF4,0xE8,0x33,0x0A,0x00,0x00};  //特征根据恶意代码反汇编选取
  if(hFindFile!=INVALID_HANDLE_VALUE) 
  {
    do
    {
      // 组成完整的待检测程序的路径
			lstrcat(szFindFile, stFindFile.cFileName);
      //调用scan_virus判断是否为病毒
      flag=scan_virus(szFindFile,0x121b,0x20,signature); 
      if(flag)
      {
        printf("%s is a virus trying to edit ur regkey of keyboard.\n",szFindFile);  //需要输出病毒详细信息
        printf("Do you want to delete it?Input 'yes' or 'no'.\n");//交互功能，如果想要删除，就会删除。
        scanf("%s",input);
        if((strcmp(input,yes)==0)||(strcmp(input,no)==0)))
        {
          if((strcmp(input,yes))==0)
          {
            remove(szFindFile);
          }
        }
        // 删除程序名称，只保留“C:\”
			  szFindFile[3] = '\0';
			  ret = FindNextFile(hFindFile, &stFindFile);
      }  
      if(!flag)
      {
        printf("%s is not a virus\n",szFindFile);
        szFindFile[3] = '\0';
	    	ret = FindNextFile(hFindFile, &stFindFile);
      }
    }while(ret!=0);//do
  }//if(hFindhandle)
  FindClose(hFindFile);
}//main
bool scan_virus(const char *FileName,long offset, int length, void *signature)
{ FILE *fp = NULL;  
 int result=0;  
 char rvir[255]={ 0 };  
 bool Flag=false;
  fp=fopen(FileName,"rb"); //以2进制打开指定文件
  if(fp==NULL)
  { return Flag; }
  fseek(fp,offset,SEEK_SET);   //把文件指针指向偏移地址
  fread(rvir,length,1,fp);         //读取length长度的代码
  result=memcmp(signature,rvir,length);  //与我们提取的代码比较，返回值放到result中
  if(result==0) 
    { Flag=true;}
    fclose(fp);   return Flag;
}
