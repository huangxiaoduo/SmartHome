/*
 * tools_link.h
 *
 *  Created on: 2012-9-28
 *      Author: chobit
 */

#ifndef TOOLS_LINK_H_
#define TOOLS_LINK_H_

#define LINK_ERROR_FAILE                -1
#define LINK_ERROR_SUCCESS              1
#define LINK_ERROR_PARAM_INVALID        (LINK_ERROR_FAILE-1)
#define LINK_ERROR_IMPLEMENT_INVALID    (LINK_ERROR_FAILE-2)
#define LINK_ERROR_SEARCH_NOTFIND       (LINK_ERROR_FAILE-3)
#define LINK_ERROR_SEARCH_FIND          (LINK_ERROR_FAILE-4)

typedef int (*fnLink_Compare)(void*hope, void* des);

typedef int (*fnLink_Free)(void* data);
typedef struct ippNode
{
    void* data;
    struct ippNode *next;
} IPPNode, *PIPPNode;

typedef struct
{
    int size;
    PIPPNode last;
    PIPPNode first;
} IPPNodeHead, *PIPPNodeHead; //链表头结点

PIPPNodeHead link_Create();
int link_Size(PIPPNodeHead head);
int link_Insert(PIPPNodeHead head, void* data, int pos);
int link_Remove(PIPPNodeHead head, int pos, PIPPNode* ret);
int link_Free(PIPPNodeHead head, fnLink_Free freefun);
int link_Get(PIPPNodeHead head, int pos, PIPPNode* ret);

int link_PushLast(PIPPNodeHead head, void* data);

int link_PopFirst(PIPPNodeHead head, void** pop);

int link_Search(PIPPNodeHead head, void* comparedata, fnLink_Compare compare, PIPPNode ret[],int* num);

int link_Find(PIPPNodeHead head, fnLink_Compare compare, PIPPNode* ret);
int link_Clear(PIPPNodeHead head);
#endif /* TOOLS_LINK_H_ */
