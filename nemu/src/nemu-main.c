#include <common.h>
word_t expr(char *e, bool *success);
void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
	printf("1111");
for(int i=0; i < argc; i++)
{
	char tmp[65536] = {0};
	word_t ans=0 ,exout;
	//sscanf(argv[i],"%s",tmp);
	printf("11111111111111111");
	bool sucs = true;
	exout = expr(tmp, &sucs);
	if(sucs)
		printf("%d %d %d\n",ans,exout,exout == ans);
	else
		printf("wrong\n");
}
/*

#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

*/

  /* Start engine. */
  /*
	engine_start();

  return is_exit_status_bad();
	*/
	return 0;
  }
