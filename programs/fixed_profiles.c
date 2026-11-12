/* Independent dihedral fixed-set audit.
 * A g-invariant set is a union of cycles of the permutation g on grid cells.
 * Enumerate those orbit unions, with exact determinant checks on adding an
 * orbit. Full-grid maximality is checked independently at each safe node.
 * Adapted by Codex on 2026-11-13 to include identity as well; all eight
 * fixed-set counts can then be combined using Burnside's lemma.
 * GCC/Clang: gcc -O3 -march=native -std=c11 -Wall -Wextra fixed_profiles.c -o fixed_profiles
 */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
typedef unsigned __int128 bits;
static int n,N,groups,cycle[100][4],length[100],chosen[21];
static bits mask[100][100],full;
static uint64_t profile[21],maximal[21],nodes;
static double now(void) {
    struct timespec t; clock_gettime(CLOCK_MONOTONIC,&t);
    return (double)t.tv_sec+1e-9*(double)t.tv_nsec;
}
static int image(int p,int g) {
    int x=p%n,y=p/n,xx=x,yy=y;
    if(g>=4) { xx=n-1-x; g-=4; }
    for(int i=0;i<g;++i) { int t=xx; xx=n-1-yy; yy=t; }
    return yy*n+xx;
}
static void dfs(int start,bits covered,int k) {
    ++nodes; ++profile[k];
    if(covered==full) ++maximal[k];
    for(int j=start;j<groups;++j) {
        if(k+length[j]>2*n) continue;
        bits c=covered; int kk=k,ok=1;
        for(int a=0;a<length[j];++a) {
            int p=cycle[j][a];
            if(c & ((bits)1<<p)) { ok=0; break; }
            c |= (bits)1<<p;
            for(int b=0;b<kk;++b) c |= mask[p][chosen[b]];
            chosen[kk++]=p;
        }
        if(ok) dfs(j+1,c,kk);
    }
}
int main(int argc,char **argv) {
    if((argc!=2 && argc!=3) || (argc==3 && strcmp(argv[2], "--nonidentity")) || (n=atoi(argv[1]))<1 || n>10) { fprintf(stderr,"usage: %s N (1..10)\n",argv[0]); return 2; }
    N=n*n;full=((bits)1<<N)-1;
    for(int a=0;a<N;++a) for(int b=a+1;b<N;++b) {
        bits m=0;
        for(int c=0;c<N;++c) if(c!=a && c!=b &&
            (b%n-a%n)*(c/n-a/n)==(b/n-a/n)*(c%n-a%n)) m |= (bits)1<<c;
        mask[a][b]=mask[b][a]=m;
    }
    const char *names[]={"identity","rotate90","rotate180","rotate270",
                         "reflect_vertical","reflect_antidiagonal","reflect_horizontal","reflect_diagonal"};
    for(int g=(argc==3 ? 1 : 0);g<8;++g) {
        double start=now();
        memset(profile,0,sizeof(profile)); memset(maximal,0,sizeof(maximal));
        memset(length,0,sizeof(length)); nodes=0;groups=0;
        int seen[100]={0};
        for(int p=0;p<N;++p) if(!seen[p]) {
            int q=p;
            do { seen[q]=1;cycle[groups][length[groups]++]=q;q=image(q,g); } while(q!=p);
            ++groups;
        }
        dfs(0,0,0);
        printf("{\"n\":%d,\"symmetry\":\"%s\",\"profile\":[",n,names[g]);
        for(int k=0;k<=2*n;++k)printf("%s%"PRIu64,k?",":"",profile[k]);
        printf("],\"maximal_profile\":[");
        for(int k=0;k<=2*n;++k)printf("%s%"PRIu64,k?",":"",maximal[k]);
        printf("],\"nodes\":%"PRIu64",\"seconds\":%.6f}\n",nodes,now()-start);
        fflush(stdout);
        fprintf(stderr,"DONE n=%d symmetry=%s nodes=%"PRIu64" seconds=%.6f\n",n,names[g],nodes,now()-start);fflush(stderr);
    }
    return 0;
}
