���̵������⣺

1������⣺NetLibs
�ⲿ�ֿⲻ�ṩԴ�룬ֻ��includeĿ¼��ͷ�ļ���lib�е�Debug��RelWithDebInfoĿ¼�µ����ӿ⡣
ĿǰWindows���Ǿ�̬���ӵģ�Linux���Ƕ�̬����

2��boost��
Ŀǰ��boost��ʹ����1.39.0�汾�����������SVN���Ѿ�����õġ����Ҫ�����ȣ�Ҫ�������²��裺
	1����boostĿ¼���Ƶ�includeĿ¼��
	2�������date_time filesystem system thread���ĸ�������ŵ�libĿ¼��(Windows��Ҫ����MultiThreaded�汾��)

3��cmake����Ŀ�
�ⲿ�ֿ���src����Դ�룬��Ҫ�ֶ����б��롣
Ŀǰ����4���⣨���Ǿ�̬���ӣ�����Ҫ�����dll�����У���
gtest 1.4.0
lua 5.1.4
luabind 0.9 ��luabind/lua_include.hpp����С�޸ģ���lua.h��λ�øĵ���lua/lua.h��
mysql-connector-c 6.0.2 �������ļ�ȥ���˲���ɵĹ��̣������������λ�ã�
			�޸���GCC�²��ܱ����Bug?��
���У�ǰ3�������ϵ���һ�������ļ��У������ĸ����ڱȽϸ��ӣ���ʱû�����ϡ�
Windows������cmake.bat���������������̣�Dependencies.sln��ǰ3�����̣�
	src/mysql-connector-c-6.0.2�ǵ�4�����̡�
	�������̷ֱ����Debug��RelWithDbgInfo�汾��ALL_BUILD���̣�
	������lib�����ɶ�Ӧ�汾�Ŀ⡣��INSTALL���̿��԰�ͷ�ļ���װ��includeĿ¼�£�
Linux������
	./configure
	./build
	��������lib�µ�Debug��RelWithDbgInfo�汾�Ŀ�
	��make install���԰�ͷ�ļ���װ��includeĿ¼�£�
	��./configure��������mysql-connector-c 6.0.2ʱ�������ɵ�����ͷ�ļ����Ƶ���includeĿ¼�£�
	��Ϊԭ�治֧��Out-of-source��Cmake��ʽ��