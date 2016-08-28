#include "trie.h"

node * create_node()
{
int i;
node *nd  = (node *) malloc (sizeof(node));

for(i=0 ;i<26 ;i++)
  nd -> nxt[i] = NULL;

nd -> prev = NULL;
nd -> word = 0;
nd -> sz = 0;
return nd;
}



void add(node *root,char *pt)
{
root->sz++;

//add(root,"rintf("%c\n",*pt); ");
if(*pt != '\0')  
  {
  node *nd =  root->nxt[(*pt)-'a'] ;
  
  if(nd == NULL)
    {
    nd = create_node(); 
    root->nxt[(*pt)-'a'] = nd;
    nd->prev = root;
    nd->cc = (*pt);
    }
   pt++; 
  add(nd,pt);
  }
else root -> word++; 
}


void show(node *root)
{
if(root == NULL) return;

show(root->prev);
printf("%c",root->cc);
}


void DFS(node *root)
{
if(root == NULL) return ;

int i;
if(root->word) {show(root);printf("\n");}

for(i=0;i<26;i++)
  DFS(root -> nxt[i]);
}


int search(node *root,char *pt)
{
if(root == NULL)
    return 0;

//add(root,"rintf("%d %c\n",root->sz,*pt); ");

if((*pt) == '\0')
    {
    DFS(root);  
    }
else
  {
    node *nd =  root->nxt[(*pt)-'a'] ;
    pt++;
    search(nd,pt);
  }
}


node* init_trie()
{
 node *root;
 root = create_node();

add(root,"bash");
add(root,"bunzip2");
add(root,"busybox");
add(root,"bzcat");
add(root,"bzcmp");
add(root,"bzdiff");
add(root,"bzegrep");
add(root,"bzexe");
add(root,"bzfgrep");
add(root,"bzgrep");
add(root,"bzip2");
add(root,"bzip2recover");
add(root,"bzless");
add(root,"bzmore");
add(root,"cat");
add(root,"chacl");
add(root,"chgrp");
add(root,"chmod");
add(root,"chown");
add(root,"chvt");
add(root,"cp");
add(root,"cpio");
add(root,"dash");
add(root,"date");
add(root,"dd");
add(root,"df");
add(root,"dir");
add(root,"dmesg");
add(root,"dnsdomainname");
add(root,"domainname");
add(root,"dumpkeys");
add(root,"echo");
add(root,"ed");
add(root,"efibootmgr");
add(root,"egrep");
add(root,"false");
add(root,"fgconsole");
add(root,"fgrep");
add(root,"findmnt");
add(root,"fuser");
add(root,"fusermount");
add(root,"getfacl");
add(root,"grep");
add(root,"gunzip");
add(root,"gzexe");
add(root,"gzip");
add(root,"hciconfig");
add(root,"hostname");
add(root,"history");
add(root,"ip");
add(root,"journalctl");
add(root,"kill");
add(root,"kmod");
add(root,"less");
add(root,"lessecho");
add(root,"lessfile");
add(root,"lesskey");
add(root,"lesspipe");
add(root,"ln");
add(root,"loadkeys");
add(root,"login");
add(root,"loginctl");
add(root,"ls");
add(root,"lsblk");
add(root,"lsmod");
add(root,"mkdir");
add(root,"mknod");
add(root,"mktemp");
add(root,"more");
add(root,"mount");
add(root,"mountpoint");
add(root,"mt");
add(root,"mv");
add(root,"nano");
add(root,"nc");
add(root,"netcat");
add(root,"netstat");
add(root,"networkctl");
add(root,"nisdomainname");
add(root,"ntfscat");
add(root,"ntfscluster");
add(root,"ntfscmp");
add(root,"ntfsfallocate");
add(root,"ntfsfix");
add(root,"ntfsinfo");
add(root,"ntfsls");
add(root,"ntfsmove");
add(root,"ntfstruncate");
add(root,"ntfswipe");
add(root,"open");
add(root,"openvt");
add(root,"pidof");
add(root,"ping");
add(root,"ping6");
add(root,"plymouth");
add(root,"ps");
add(root,"pwd");
add(root,"rbash");
add(root,"readlink");
add(root,"red");
add(root,"rm");
add(root,"rmdir");
add(root,"rnano");
add(root,"sed");
add(root,"setfacl");
add(root,"setfont");
add(root,"setupcon");
add(root,"sh");
add(root,"sleep");
add(root,"ss");
add(root,"stty");
add(root,"su");
add(root,"sync");
add(root,"systemctl");
add(root,"systemd");
add(root,"tailf");
add(root,"tar");
add(root,"tempfile");
add(root,"touch");
add(root,"true");
add(root,"udevadm");
add(root,"umount");
add(root,"uname");
add(root,"uncompress");
add(root,"vdir");
add(root,"wdctl");
add(root,"which");
add(root,"whiptail");
add(root,"ypdomainname");
add(root,"zcat");
add(root,"zcmp");
add(root,"zdiff");
add(root,"zegrep");
add(root,"zfgrep");
add(root,"zforce");
add(root,"zgrep");
add(root,"zless");
add(root,"zmore");
add(root,"znew");

return root;
}
