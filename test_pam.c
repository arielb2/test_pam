#include <security/pam_appl.h>
#include <sys/types.h>
#include <security/pam_misc.h>

#include <stdio.h>
int pam_set_item(pam_handle_t *pamh, int item_type, const void *item);
int main(int argc, char *argv[])
{
   int res;
   //const pam_handle_t *pamh = NULL;
   const char *user="arielb";
   const void *item;
// const struct pam_conv *pam_conv;
   
   pam_handle_t* pamh; 
   struct pam_conv pamc; 

   pamc.conv = &misc_conv; 
   pamc.appdata_ptr = NULL; 
    
   res = pam_start("check",user, &pamc, &pamh);
   if (res == 0)
   {
      printf("Contexto inicializado...[%d]\n", res);
   }
   else
   {
      printf("Error al iniciar [%d] - %s ", res, pam_strerror(pamh, res));
   }
   //res = pam_get_item(pamh, PAM_SERVICE, &item);
   char **list ;
   list = pam_getenvlist(pamh);
   printf("Resultado %s \n", *list);
   pam_end (pamh, 0);
   printf("test succes\n");
   return 0;
}
