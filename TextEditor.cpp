#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
	char data;
	struct node* next;
	struct node* prev;
};
struct node* head;
struct node* copi;

struct node* NodNou(char x)
{
	struct node* newNode
			=(struct node*)malloc(sizeof(struct node*));
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}
void InsertAtTail(char x)
{
	struct node* temp = head;
	struct node* newNode = NodNou(x);
	if(head==NULL)
	{
		head=newNode;
		return;
	}
	while(temp->next != NULL) temp=temp->next;
	temp->next = newNode;
	newNode->prev = temp;
}
void Print()
{
	struct node* temp = head;
	while(temp!= NULL)
	{
		printf("%c", temp->data);
		temp=temp->next;
	}
	printf("\n");
}

struct node * move(int *cursor)
{
			
		int i=0;
		struct node* temp=head;
		if((*cursor)>=0)
		{
			
			for(i=1;i<(*cursor);i++)
			{
				if(temp->next==NULL)
				{
					printf("Nu te poti misca mai departe!");
					return temp;
				}
				else
				{
					temp=temp->next;	
				}
			}
		}
	
		if((*cursor)<=0)
		{
			for(i=-500;i>(*cursor);i--)
			{

				if(temp->prev==head)
				{
					printf("AI ajuns pe prima pozitie!");
					return head;
				}
				else
				{
					temp=temp->prev;
				}
			}
		}
		return temp;
}
struct node* del(int *cursor,int nr_stergeri)
{
	int i;
	printf("\nIn del\n");
	Print();
	struct node *q = move(cursor);
	struct node *p;
	if(head==NULL)
	{
		printf("Lista goala");
		exit(1);
	}
	if((*cursor)==0)
	{
		for(i=0;i<nr_stergeri && (q!=NULL);i++)
		{
			q=head;
			head=head->next;
			free(q);
			q=head;

		}

		head->prev=NULL;
	}
	else
	{
	    for(i=0;i<nr_stergeri;i++)
	    {
	    	p=q->next;
			q->next=q->next->next;
			p->next->prev=q;
			free(p);
	    }
	}
	Print();
}
void backspace(int *cursor)
{
	int i;
	struct node *q = move(cursor);
	if(head==NULL)
	{
		printf("Lista goala");
		exit(1);
	}
	struct node *p;
	for(i=0;i<1;i++)
	{
		if(q->prev!=NULL && q->prev != head)
		{
			p=q;
			p->prev->next=p->next;
			p->next->prev=p->prev;
			free(p);
			return;
		}
		else
			if(q==head)
		{
			q=head;
			head=head->next;
			head->next->prev=NULL;
			free(q);
			return;
		}
	}
}

struct Node *insertString(int *cursor,char y[100])
{
	char x;
	int i=0,len;
	len=strlen(y);
	printf("\nLungimea: %d\n",len);
	struct node* q = move(cursor);
	if(q!=head && q!=NULL)
	{
		for(i=0;i<len;i++)
		{

			struct node* newNode = NodNou(y[i]);
			{
				newNode->next=q->next;
				newNode->prev=q;
				q->next=newNode;
				q->next->prev=newNode;
				q=q->next;
			}
		
		}
		return;
	}
	else
	{
		
			while(q==head)
			{
				i=0;
					struct node* newNode = NodNou(y[i]);	
					newNode->next=head;
					newNode->prev=NULL;
					head->prev=newNode;
					head=newNode;
					i=i+1;
			}
			if(q->prev==head)
			{
				struct node* curent;
				curent=head;
				for(i=1;i<len;i++)
				{
					struct node* newNode = NodNou(y[i]);
					{	
						curent->next->prev=newNode;
						newNode->next=curent->next;
						curent->next=newNode;
						newNode->prev=curent;

					}
					curent=curent->next;
				}
			}
		
	}
	
		(*cursor)=(*cursor)+len;
	
	Print();
} 
char *copy(int *cursor,int x)
{
	char sri[100];

	struct node* q = move(cursor);
	if(q==NULL)
	{
		printf("nu exitsta nod la pozitia setata");
		exit(1);
	}
	
	for(int i=0;i<x;i++)
	{
		sri[i]=q->data;
		q=q->next;
	}
	return sri;
}
void paste(int *cursor,char e[])
{
	insertString(cursor,e);
}
struct node* undo()
{

}
int main(int argc, char *argv[])
{
	head = NULL;
	struct node* ko;
	int t=0;
	int *cursor;
	char k;

	FILE *fp;
		fp=fopen(argv[1],"r");
	if(!fp)
	{
		printf("Eroare la deschiderea fisierului!");
		exit(1);
	}
	while((k=getc(fp))!=EOF)
	{
		InsertAtTail(k);
	}
	Print();
	fclose(fp);	
	FILE *pp;
		pp=fopen(argv[2],"r");
	if(!pp)
	{
		printf("eroare la deschiderea fisierului");
		exit(1);
	}
	// operatiile
	int counter;
	char y[1000];
	int x=0;
	
		counter=getc(pp)-'0';
		int ok=0;
		int help=0;

		int s=0;
		t=s;
		cursor=&t;
		for(int i=0;i<counter;i++)
		{
			if(fscanf(pp,"%s",y))
					{
					
					if(strcmp(y,"move")==0)
					{
							if(ok==0)
							{
								fscanf(pp,"%d",&s);
								(*cursor)=(*cursor)+s;
								move(cursor);
								
							}
					}
					if(strcmp(y,"backspace")==0)
					{
						
						backspace(cursor);
						(*cursor)=(*cursor)-1;	

					}
					
						if (strcmp(y,"del")==0)
						{
							fscanf(pp,"%d",&x);
							
							
							del(cursor,x);
							
						}
				
						if (strcmp(y,"insert")==0)
						{
						
							fscanf(pp,"%s",y);

							insertString(cursor,y);

						}
						char f[100]="";
						if(strcmp(y,"copy")==0)
						{
							
							strcpy(f,copy(cursor,x));
						}
						if(strcmp(y,"paste")==0)
						{
							paste(cursor,f);
						}
					}
			}
	fclose(pp);
	FILE *out;
	out=fopen(argv[3],"wt");
	if(out==NULL)
	{
		printf("Fisierul nu a putut fii deschis!");
	}
	int qw=0;
	for(ko=head;ko!=NULL;ko=ko->next)
	{
		qw++;
		fputc(ko->data,out);
	}
	fclose(out);
	return 0;
}