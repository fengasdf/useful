

#include "hafu.h"
#include<ctime>

void add()
{
	//
	time_t now_time;
	time_t cur;
	hufffz a;
	now_time = time(NULL);
	a.trans("E:\\test2.txt");
	cur = time(NULL);
	cout << cur - now_time << endl;
	a.restore("E:\\test2code.txt");

	now_time = time(NULL);
	cout << now_time - cur << endl;
	//////FILE *f = NULL;
	////errno_t  error = fopen_s(&f, "E:\\test2.txt", "a+");
	////if (error)
	////{
	////	
	////	throw 1;
	////}
	////int va = 0;
	////fscanf_s(f, "%d", &va, 3);
	////va = fgetc(f);
	//unsigned char c = 0xfe;
	//int ai = c;
	//
	//FILE *f = NULL;
	//fopen_s(&f, "E:\\Readme.txt", "wb");
	//int sum = 255;
	//fwrite(&sum, 1, 1, f);

	//fclose(f);
	//////fclose(f);
	//FILE *file = NULL;

	///*string s = "225";*/
	//fopen_s(&file, "E:\\Readme.txt", "rb");
	//int va = 0;
	//fread(&va, 1, 1, file);

	//fclose(file);

	//FILE *f = NULL;
	//fopen_s(&f, "E:\\test8code.txt", "w");
	////sum = fgetc(file);
	//fprintf(file, "%d", 26 );
	/*fgets(ch, 20, f);*/
	{

		/*fputc(va, f);*/

	}
}

int main()
{
	add();
	getchar();
	return 0;

}