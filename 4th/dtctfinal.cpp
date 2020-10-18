#include <stdio.h>
#include <string.h>
#include <windows.h>
bool scan_virus(const char *FileName,long offset, int length, void *signature);
void main()
{ WIN32_FIND_DATA stFindFile;
  HANDLE hFindFile;
  char *szFilter = "*.exe";   
  char szFindFile[MAX_PATH];  
  char szSearch[MAX_PATH];    
  int ret = 0;                
  lstrcpy(szFindFile,"C:\\");
  lstrcpy(szSearch,"C:\\");
  lstrcat(szSearch, szFilter);
  hFindFile = FindFirstFile(szSearch, &stFindFile);
  bool flag=false;
  char input[10];
  char yes[10]="yes";
  char no[10]="yes";
  unsigned char signature[]=
  {0x8B,0xF4,0x6A,0x78,0x8D,0x4D,0x80,0x51,0x6A,0x03,0x6A,0x00,0x68,0x40,0x50,0x42,
   0x00,0x8B,0x55,0xFC,0x52,0xFF,0x15,0xD0,0xB1,0x42,0x00,0x3B,0xF4,0xE8,0x33,0x0A,0x00,0x00};
  if(hFindFile!=INVALID_HANDLE_VALUE) 
  {
    do
    {
	  lstrcat(szFindFile, stFindFile.cFileName);
      flag=scan_virus(szFindFile,0x121b,0x20,signature); 
      if(flag)
      {
        printf("%s is a virus trying to edit ur regkey of keyboard.\n",szFindFile);
        printf("Do you want to delete it?Input 'yes' or 'no'.\n");
        scanf("%s",input);
        if((strcmp(input,yes)==0)||(strcmp(input,no)==0))
        {
          if((strcmp(input,yes))==0)
          {
            remove(szFindFile);
          }
        }
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
  fp=fopen(FileName,"rb"); 
  if(fp==NULL)
  { return Flag; }
  fseek(fp,offset,SEEK_SET);
  fread(rvir,length,1,fp); 
  result=memcmp(signature,rvir,length); 
  if(result==0) 
    { Flag=true;}
    fclose(fp);   return Flag;
}
