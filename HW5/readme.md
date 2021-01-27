# HW5
# (1) Result screenshot
![image0](https://github.com/auyu0408/DS/blob/main/HW5/screenshot.png)  
![image1](https://github.com/auyu0408/DS/blob/main/HW5/screenshot2.png)  
Screenshot of command line.  
![image2](https://github.com/auyu0408/DS/blob/main/HW5/screenshot3.png)  
Screen shot of output.txt.  
# (2) Program architecture
![image3](https://github.com/auyu0408/DS/blob/main/HW5/image.png)  
# (3) Program functions
 ```c  
#define TABLE_SIZE 13
#define PRIME 7
``` 
## **Parameters**  
**TABLE_SIZE**：在題目裡面是13，區分的空間數  
**PRIME**：在題目裡面是7，和TABLE_SIZE均可隨意更改，為了方便更改做了**MACRO**   define  
``` C
int key;
int check[TABLE_SIZE]={0},hash[TABLE_SIZE]={0};
``` 
## **Parameters**  
**key**：準備hash的數  
**check[TABLE_SIZE]**：初始值均為0，代表沒存東西，當hash的x格存入數字時，則check的相對應格會變成1。這是為了避免key是0的情況，導致無法分辨hash內存的值到底是初始值或是經過hash的  
**hash[TABLE_SIZE]**：hash完後的結果會存至這邊，一開始均存為0  
``` C
while(scanf("%d",&key)!=EOF)
//因為input僅有一行數字，所以可以一次讀入一數直到文件末端
{
    int temp=key%TABLE_SIZE;
//當i=0時，hash function的簡化，hash2會等於0，只留下hash1
    if(check[temp]==0)
//如果這個格子還沒填入任何數字，那就可以把key hash進去，並且check表的狀態會變更為已經存入數字，然後直接到一開始讀入下一個數字
    {
        hash[temp]=key;
        check[temp]=1;
        continue;
    }
    do
//當發生collision時，把hash2加進來，每次i+1時，其實hash function 的結果即為原結果加上PRIME-(key%PRIME)，最後mod TABLE_SIZE是當它超過TABLE_SIZE拾取其餘數即可。而當check表內已經存過數字的話，代表i要再+1
    {
        temp=(temp+PRIME-(key%PRIME))%TABLE_SIZE;
    }while (check[temp]==1);
    hash[temp]=key;
    check[temp]=1;
//當終於沒有collision時，做法和一開始一樣
}
``` 
## **Parameters**
**temp**：暫時儲存key經過hash function後的結果，並用來比對是否會造成collision  
``` C
printf("%d->%d",0,hash[0]);
//因為第一行不該換行，所以直接印出
for(int i=1;i<TABLE_SIZE;i++)
//第一個數之後，均先換行再印下一個數
{
    printf("\n%d->%d",i,hash[i]);
}
``` 
## **return value**
當整個main function順利跑完，return 0並結束程式