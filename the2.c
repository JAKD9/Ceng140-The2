#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node { 
	int data;
	struct node *next;
};
struct message_node{
	int sender_id;
	int topic_id;
	int message_id;
	struct message_node *next;
};
struct topic_node{
	char *topic_name;
	int topic_id;
	struct node *follower_list; /*hold user ID's in data field*/
	struct topic_node *next;
	
	/*Add additional fields as needed*/
};
struct user_node{
	char *user_name;
	int user_id;
	struct node *followed_topics; /*hold topic ID's in data field*/
	struct message_node *inbox;
	struct user_node *next;
	/* Add additional fields as needed */
};
typedef struct node NODE;
typedef struct message_node MESSAGES;
typedef struct topic_node TOPICS;
typedef struct user_node USERS;

NODE* add_node(int data)
{
	NODE* new_node=(NODE *)malloc(sizeof(NODE));
	if(new_node)
	{
		new_node->data=data;
		new_node->next=NULL;
	}
	return new_node;
}
USERS* add_user(int id, char *name)
{
	USERS *new_user=(USERS *)malloc(sizeof(USERS));
	if(new_user)
	{
		new_user->user_name=(char *)malloc(sizeof(char)*21);
		strcpy(new_user->user_name,name);
		new_user->user_id=id;
		new_user->followed_topics=NULL;
		new_user->inbox=NULL;
		new_user->next=NULL;	
	}
	return new_user;
} 
TOPICS* add_topic(int id, char *name)
{
	TOPICS *new_topic=(TOPICS *)malloc(sizeof(TOPICS));
	if(new_topic)
	{
		new_topic->topic_name=(char *)malloc(sizeof(char)*21);
		strcpy(new_topic->topic_name,name);
		new_topic->topic_id=id;
		new_topic->follower_list=NULL;
		new_topic->next=NULL;
	}
	return new_topic;
}
MESSAGES* add_message(int sid, int tip, int mid)
{
	MESSAGES *new_message=(MESSAGES *)malloc(sizeof(MESSAGES));
	if(new_message)
	{
		new_message->sender_id=sid;
		new_message->topic_id=tip;
		new_message->message_id=mid;
		new_message->next=NULL;
	}
	return new_message;
}	
int main(void)
{
	char *command=(char *)malloc(sizeof(char)*21);
	int i_command;
	char *username=(char *)malloc(sizeof(char)*21);
	char *topicname=(char *)malloc(sizeof(char)*21);
	int user_id=0;
	int topic_id=0;
	int message_id=0;
	int id;
	int tip;
	int control;
	USERS *i;
	TOPICS *j;
	NODE *k;
	MESSAGES *t;
	USERS *head_users=NULL;
	TOPICS *head_topics=NULL;
	
	NODE *nbefore,*ncurrent;
	MESSAGES *mbefore,*mcurrent;
	USERS *ubefore,*ucurrent;

	while(scanf("%s",command)!=EOF)
	{
		nbefore=NULL;
		mbefore=NULL;
		ubefore=NULL;
		if(!strcmp(command,"ADD"))
			i_command=0;
		else if(!strcmp(command,"SUBSCRIBE"))
			i_command=1;
		else if(!strcmp(command,"SEND")||!strcmp(command,"WRITE"))
			i_command=2;
		else if(!strcmp(command,"UNSUBSCRIBE"))
			i_command=3;
		else if(!strcmp(command,"DELETEUSER"))
			i_command=4;
		switch(i_command)
		{
			case 0 :
				scanf("%s",username);
				user_id+=1;
				if(!(head_users))
				{
					(head_users) = add_user(user_id, username);
				}
				else
				{

					for(i=head_users;i->next!=NULL;i=i->next);
					i->next=add_user(user_id, username);	
				}
				break;
			case 1 :
				scanf("%s ",username);
				scanf("%s",topicname);
				for(i=head_users;i!=NULL;i=i->next)
				{
					if(!strcmp(i->user_name,username))
					{
						id=i->user_id;
						break;
					}
				}
				if(!(head_topics))
				{
					topic_id+=1;
					(head_topics)=add_topic(topic_id, topicname);
					(head_topics)->follower_list=add_node(id);
					if(!(i->followed_topics))
					{
						i->followed_topics=add_node(topic_id);
					}
					else
					{
						for(k=i->followed_topics;k->next!=NULL;k=k->next);
						k->next=add_node(topic_id);
					}
				}
				else
				{
					control=0;
					for(j=head_topics;j!=NULL;j=j->next)
					{
						if(!(strcmp(j->topic_name,topicname)))
						{
							control=1;
						}
					}
					if(control==0)
					{
						topic_id+=1;
						for(j=head_topics;j->next!=NULL;j=j->next);
						j->next=add_topic(topic_id, topicname);
						j=j->next;
						j->follower_list=add_node(id);
						if(!(i->followed_topics))
						{
							i->followed_topics=add_node(topic_id);
						}
						else
						{
							for(k=i->followed_topics;k->next!=NULL;k=k->next);
							k->next=add_node(topic_id);
						}
					}
					else if(control==1)
					{
						for(j=head_topics;j!=NULL;j=j->next)
						{
							if(!(strcmp(j->topic_name,topicname)))
							{
								break;
							}
						}
						tip=j->topic_id;
						if(!(j->follower_list))
						{
							j->follower_list=add_node(id);
						}
						else
						{
							for(k=j->follower_list;k->next!=NULL;k=k->next);
							k->next=add_node(id);
						}
						if(!(i->followed_topics))
						{
							i->followed_topics=add_node(tip);
						}
						else
						{
							for(k=i->followed_topics;k->next!=NULL;k=k->next);
							k->next=add_node(tip);
						}
					}
				}
				
				
				break;
			case 2 :
				scanf("%s ",username);
				scanf("%s",topicname);
				message_id+=1;			
				for(j=head_topics;j!=NULL;j=j->next)
				{
					if(!strcmp(j->topic_name,topicname))
					{
						tip=j->topic_id;
						break;
					}
				}
				for(i=head_users;i!=NULL;i=i->next)
				{
					if(!strcmp(i->user_name,username))
					{
						id=i->user_id;
						break;
					}
				}
				if(!(i->inbox))
				{
					i->inbox=add_message(id,tip,message_id);
				}
				else
				{
					for(t=i->inbox;t->next!=NULL;t=t->next);
					t->next=add_message(id,tip,message_id);
				}
				for(i=head_users;i!=NULL;i=i->next)
				{
					if(i->user_id==id)
					{
						continue;
					}
					for(k=i->followed_topics;k!=NULL;k=k->next)
					{
						if(k->data==tip)
						{
							if(!(i->inbox))
							{
								i->inbox=add_message(id,tip,message_id);
							}
							else
							{
								for(t=i->inbox;t->next!=NULL;t=t->next);
								t->next=add_message(id,tip,message_id);
							}	
						}
					}
				}
				break;
			case 3 :
				scanf("%s ",username);
				scanf("%s",topicname);
				for(i=head_users;i!=NULL;i=i->next)
				{
					if(!strcmp(i->user_name,username))
					{
						id=i->user_id;
						break;
					}
				}
				for(j=head_topics;j!=NULL;j=j->next)
				{
					if(!strcmp(j->topic_name,topicname))
					{
						tip=j->topic_id;
						break;
					}
				}
				while(1)
				{
					mbefore=NULL;
					control=0;
					for(t=i->inbox;t!=NULL;t=t->next)
					{
						mcurrent=t;
						if(tip==t->topic_id)
						{
							control=1;
							break;
						}
						mbefore=t;
					}
					if(control)
					{
						if(mbefore)
						{
							if(mcurrent->next)
							{mbefore->next=mcurrent->next;}
							else
							{
								mbefore->next=NULL;
							}
					
						}
						else
						{
							if(mcurrent->next)
							{i->inbox=mcurrent->next;}
							else
							{
								i->inbox=NULL;
							}
						}
						if(mcurrent)
						{
							free(mcurrent);
						}
					}
					else
					{
						break;
					}
				}
				nbefore=NULL;
				for(k=j->follower_list,control=0;k!=NULL;k=k->next)
				{
					ncurrent=k;
					if(id==k->data)
					{
						control=1;
						break;
					}
					nbefore=k;
				}
				if(control)
				{
					if(nbefore)
					{
						if(ncurrent->next)
						{nbefore->next=ncurrent->next;}
						else
						{
							nbefore->next=NULL;
						}
					}
					else
					{
						if(ncurrent->next)
						{j->follower_list=ncurrent->next;}
						else
						{
							j->follower_list=NULL;
						}
					
					}
					if(ncurrent)
					{
						free(ncurrent);
					}
				}
				nbefore=NULL;
				for(k=i->followed_topics,control=0;k!=NULL;k=k->next)
				{
					ncurrent=k;
					if(tip==k->data)
					{
						control=1;
						break;
					}
					nbefore=k;
				}
				if(control)
				{
					if(nbefore)
					{
						if(ncurrent->next)
						{nbefore->next=ncurrent->next;}
						else
						{
							nbefore->next=NULL;
						}
					}
					else
					{
						if(ncurrent->next)
						{i->followed_topics=ncurrent->next;}
						else
						{
							i->followed_topics=NULL;
						}
					}
					if(ncurrent)
					{
						free(ncurrent);
					}
				}
				break;


			case 4 :
				scanf("%s,",username);
				for(i=head_users,control=0;i!=NULL;i=i->next)
				{
					ucurrent=i;
					if(!strcmp(i->user_name,username))
					{
						id=i->user_id;
						control=1;
						break;
					}
					ubefore=i;
				}
				if(control)
				{
					if(ubefore)
					{
						if(ucurrent->next)
						{
							ubefore->next=ucurrent->next;
						}
						else
						{
							ubefore->next=NULL;
						}
					}
					else
					{
						if(ucurrent->next)
						{
							head_users=ucurrent->next;
						}
						else
						{
							head_users=NULL;
						}
					}
					if(ucurrent)
					{
						free(ucurrent);	
					}
				}
				for(i=head_users;i!=NULL;i=i->next)
				{
					while(1)
					{
						mbefore=NULL;
						control=0;				
						for(t=i->inbox;t!=NULL;t=t->next)
						{
					
							mcurrent=t;
							if(id==t->sender_id)
							{
								control=1;
								break;
							
							}
							mbefore=t;
						}
						if(control)
						{
							if(mbefore)
							{
								if(mcurrent->next)
								{
									mbefore->next=mcurrent->next;
								}
								else
								{
									mbefore->next=NULL;
								}
							}
							else
							{
								if(mcurrent->next)
								{
									i->inbox=mcurrent->next;
								}
								else
								{
									i->inbox=NULL;
								}
							}
							if(mcurrent)
							{
								free(mcurrent);
							}
						}
						else
						{
							break;
						}
					}
				}
				break;
		}  
	}	
	for(i=head_users;i!=NULL;i=i->next)
	{
		printf("%d:",(i)->user_id);
		for(t=i->inbox;t!=NULL;t=t->next)
		{
			if(!(t->next))
			{printf(" %d",t->message_id);}
			else
			{
				printf(" %d",t->message_id);
			}
		}
		printf("\n");
	}
	
	
	return 0;
}
