#visual studio
```
1����vs ������Ա����(Visual Studio Command Prompt)��ʹ��cl����
cl ex.cpp /d1 reportSingleClassLayoutBaseAA /EHsc
2���Ҽ���Ҫ��ʾ��*.cpp >> ���� >> ������ >> ����ѡ��
������ѡ������ӣ�
/d1 reportSingleClassLayoutXXX  (XXXָ����Ҫ��ʾ����)
�������vs���棬ֱ�ӱ����ʱ��ͻ�����ڴ沼�֣�����Ҫ���ӣ�
ʹ��reportAllClassLayout������ܶ���Ϣ���ô�����


����ǵ�����дһ��Դ�ļ����鿴���֣�������ע��ģ�ʹ�õ���VS2015��Command Prompt����
ֻд�࣬��дmain��������������󲼾ֺ��麯�����֣����ǻ���ʾLINK : fatal error LNK1561: ���붨����ڵ㣻ֻ��дһ��main�����壬return 0;
����������Ҳ����������󲼾ֺ��麯������
��ʹ��reportSingleClassLayoutʱ�����ҵķ�ʽ�ǰ������������Base��BaseV���������Base��������Ĳ��ֶ������
```

#gcc
```
g++ -fdump-class-hierarchy mode.cc
```

#clang
```
�鿴���󲼾�
clang -Xclang -fdump-record-layouts -stdlib=libc++ -std=c++11 -c ex.cpp
�鿴�麯������
clang -Xclang -fdump-vtable-layouts -stdlib=libc++ -std=c++11 -c ex.cpp

û�ҵ����ֻ���һ���࣬������������������Ĳ���
����û��main������������Ҫ����һ����Ķ���Ż�������󲼾ֺ��麯������
-std=c++11 ���Ա�����-Wc++11-extensions�ľ���
```