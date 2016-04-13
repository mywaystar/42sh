#include <parser.h>
#include <stdio.h>

void debug_put_process(t_process *p)
{
	printf("Process:\n");
	for (int i = 0; p->argv[i]; i++) {
		printf("%s ", p->argv[i]);
	}
	printf("\nstdin: %d, stdout: %d, stderr: %d\n", p->stdio[0].fd, p->stdio[1].fd, p->stdio[2].fd);
}

void debug_put_job(t_job *j)
{
	t_list 		*process_list;

	process_list = j->process_list;
	printf("\nNEW JOB===========\n");
	while (process_list) {
		debug_put_process(process_list->content);
		process_list = process_list->next;
	}
	if (j->linker == LINK_THEN)
		printf("\nLink: 	THEN\n");
	if (j->linker == LINK_AND)
		printf("\nLink: 	AND\n");
	if (j->linker == LINK_OR)
		printf("\nLink: 	OR\n");
	if (j->linker == LINK_TO_BACKGROUND)
		printf("\nLink: 	TO_BACKGROUND\n");
}

int main(void)
{
	char *cmd;
	t_list *token_list;
	t_list *job_list;

	cmd = "ls|wc";
	printf("\nTesting: %s\n", cmd);
	token_list = input_to_token_list(cmd);
	job_list = token_list_to_job_list(token_list);
	printf("done\n");
	while (job_list){
		debug_put_job(job_list->content);
		job_list = job_list->next;
	}

	cmd = "ls > wc 'yo yo yo'-l -L -lL|wc|wc|   wc&&false|cat -e      		| wc       ||        true; ;yes";	
	printf("\nTesting: %s\n", cmd);
	token_list = input_to_token_list(cmd);
	job_list = token_list_to_job_list(token_list);
	while (job_list){
		debug_put_job(job_list->content);
		job_list = job_list->next;
	}
}