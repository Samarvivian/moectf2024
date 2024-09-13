#include <stdio.h>  
#include <stdint.h>  
  
//加密函数  
void encrypt (uint32_t* v, uint32_t* k) {  
    uint32_t v0=v[0], v1=v[1], sum=0, i;           /*将传进函数的v分解成两个32位无符号数v0，v1 */  
    uint32_t delta=0x9e3779b9;                     /*使用的加密常数，为黄金分割率，题目一般会改 */  
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* 密钥分别取出，方便后续的操作 */  
    for (i=0; i < 32; i++) {                       /* 32轮*/  
        sum += delta;  
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);  
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);  
    }                                           
    v[0]=v0; v[1]=v1;  //将加密完毕的两个数值放回
}  
//解密函数  
void decrypt (uint32_t* v, uint32_t* k) {  
    uint32_t v0=v[0], v1=v[1], sum=0xC6EF3720, i;  /*此处的sum是由一开始的黄金分割率迭代32轮之后得到的数*/  
    uint32_t delta=0x9e3779b9;                     
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* key不变 */  
    for (i=0; i<32; i++) {                         /* 依然是32轮*/  
        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);  	//加密是加，解密即是减，由图可知，先解v1再解v0
        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);  
        sum -= delta;  
    }                                           
    v[0]=v0; v[1]=v1;  
}  
  
int main()  
{  
    uint32_t v[2]={1,2},k[4]={2,2,3,4};  
    // v为要加密的数据是两个32位无符号整数  
    // k为加密解密密钥，为4个32位无符号整数，即密钥长度为128位  
    printf("加密前原始数据：%u %u\n",v[0],v[1]);  
    encrypt(v, k);  
    printf("加密后的数据：%u %u\n",v[0],v[1]);  
    decrypt(v, k);  
    printf("解密后的数据：%u %u\n",v[0],v[1]);  
    return 0;  
}  

