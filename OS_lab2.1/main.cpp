//
//  main.cpp
//  lab2 OS
//
//  Created by MacBook Pro on 2/28/19.
//  Copyright © 2019 MacBook Pro. All rights reserved.
//
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
using  namespace std;
pthread_mutex_t mutex1;//объявить идентификатор мьютекса /*неименованного семафора*/;

void* func1(void* temp1)//функция потока 1()
{
    cout<<"\nthe thread1 started working\n";
    while (*((bool*)temp1))//пока (флаг завершения потока 1 не установлен)
    {
        pthread_mutex_lock(&mutex1);//захватить мьютекс /*неименованный семафор*/;
        for(int i=0; i<5;i++)            //в цикле 5 раз выполнять
        {
            std::cout<<'1'<<std::flush;//выводить символ ‘1’ на экран;
            sleep(1);                                    //задержать на время;
        }
        pthread_mutex_unlock(&mutex1);//освободить мьютекс /*неименованный семафор*/;
        sleep(1);                                        //задержать на время;
    }
    return 0;
}

void* func2(void* temp2)
{
    cout<<"\nthe thread2 started working\n";
    while (*((bool*)temp2))
    {
        pthread_mutex_lock(&mutex1);
        for(int i=0; i<5;i++)
        {
            std::cout<<'2'<<std::flush;
            sleep(1);
        }
        pthread_mutex_unlock(&mutex1);
        sleep(1);
    }
    return 0;
}

int main(){
    
    bool flag1=true,flag2=true;
    pthread_t t1; //объявить идентификатор потока 1;
    pthread_t t2; //объявить идентификатор потока 2;
    pthread_mutex_init (&mutex1,NULL); //инициализировать мьютекс /*неименованный семафор*/;
    pthread_create(&t1,NULL,&func1,&flag1); //создать поток из функции потока 1;
    pthread_create(&t2,NULL,&func2 ,&flag2); //создать поток из функции потока 2;
    cout<<"Prees Enter button to finish the programm\n";
    getchar(); //ждать нажатия клавиши;
    flag1=false;flag2=false; //установить флаг завершения потока 1 и 2;
    pthread_join(t1,NULL); //ждать завершения потока 1;
    pthread_join(t2,NULL); //ждать завершения потока 2;
    pthread_mutex_destroy(&mutex1); //удалить мьютекс /*неименованный семафор*/;
    cout<<"\nThe End\n";
}
