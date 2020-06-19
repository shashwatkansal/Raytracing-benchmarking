/*
 * Filename     : cpu_json.c
 * Last Modified: 19 June 2020
 * Owner        : Group 20
 * 
 * Description: 
 * Contains functions which extract model name , clock frequency and
 * number of physical cores from /proc/cpuinfo along with hostname. This is the 
 * dumped in a json file which is sent to a database using a POST request. The 
 * requests are handled by postcpuinfo.py .
 * Other: 
 * Make sure that you have postcpuinfo.py otherwise the data won't go to the
 * database.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* cpu_model_name(void) {
  FILE *sysinf = fopen("/proc/cpuinfo", "r");
   char *line = 0;
   size_t length = 0;
   //proc stores information separately for every 'virtual' processor
   //so only reads info for processor 0
   int core_counter = 0;

   while(getline(&line, &length,  sysinf) != -1 && core_counter < 1)
   {
      
      if(strstr(line, "model name")!= NULL){
        char *info = strstr(line, ":");
        core_counter+=1;
        //remove ': '
        return strtok(info+2,"\n");
      }
      
   }

   free(line);
   fclose(sysinf);
   return NULL;
}

float cpu_clock_frequency(void) {
  FILE *sysinf = fopen("/proc/cpuinfo", "r");
   char *line = 0;
   size_t length = 0;
   //proc stores information separately for every 'virtual' processor
   //so only reads info for processor 0
   int core_counter = 0;
   

   while(getline(&line, &length,  sysinf) != -1 && core_counter < 1 )
   {
      
      if(strstr(line, "cpu MHz")!= NULL){
        char *info = strstr(line, ":");
        core_counter+=1;
        //remove ': '
        return atof(info+2);
      }
      
   }
   
   free(line);
   fclose(sysinf);
   return 0;
   
}



int physical_cpu_cores(void) {
  FILE *sysinf = fopen("/proc/cpuinfo", "r");
   char *line = 0;
   size_t length = 0;
   //proc stores information separately for every 'virtual' processor
   //so only reads info for processor 0
   int core_counter = 0;
   

   while(getline(&line, &length,  sysinf) != -1 && core_counter < 1)
   {
      
      if(strstr(line, "cpu cores")!= NULL){
        char *info = strstr(line, ":");
        core_counter+=1;
        //remove ': '
        return atoi(info+2);
      }
      
   }
   
   free(line);
   fclose(sysinf);
   return 0;
}

int main() {
    char *sentence;
    //linux hostnames are limited to 253 characters
    char sysname[254];
    gethostname(sysname, 254);

    /* Start making the json dump */
    FILE *b_fp, *t_fp;
    b_fp = fopen("benchmark.json", "w");
    t_fp = fopen("tracer-result.txt", "r");

    /* Read in the tracer result */
    float time;
    fscanf(t_fp, "%f", &time);

    fprintf(b_fp, "%s", "{\"entry\":{\"procName\":\"");
    fprintf(b_fp, "%s", cpu_model_name());
    fprintf(b_fp, "%s", "\",\"noProcs\":");
    fprintf(b_fp, "%d", physical_cpu_cores());
    fprintf(b_fp, "%s", ",\"clockFreq\":");
    fprintf(b_fp, "%f", cpu_clock_frequency());
    fprintf(b_fp, "%s", ",\"sysName\":\"");
    fprintf(b_fp, "%s", sysname);
    fprintf(b_fp, "%s", "\",\"time\":");
    fprintf(b_fp, "%f", time);
    fprintf(b_fp, "%s", "}}");
    fclose(b_fp);
    fclose(t_fp);
}
