#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
int main(int argc, char** argv) {
    if (argc < 3) return 1;
    pid_t pid = fork();
    if (pid == 0) { execvp(argv[2], &argv[2]); _exit(127); }
    sleep(std::stoul(argv[1]));
    kill(pid,SIGTERM); waitpid(pid,nullptr,0);
    return 124;
}
