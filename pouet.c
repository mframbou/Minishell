/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 20-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 20-01-2022 00:11 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include<stdio.h>
#include<unistd.h>
#include<signal.h>


void
sigusr1( int pidno )
{
  fprintf(stderr, "Caught\n");
}

int
main()
{
  pid_t pid;

  signal( SIGINT, sigusr1 );
  if( (pid = fork()) == 0 ){
    pause();
    fprintf(stderr, "Child\n");
  }
  else
  {
    fprintf(stderr, "Parent\n");
    kill( pid , SIGINT ); //parent sends signal to child
  }
  pause();
  return 0;
}