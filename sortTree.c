#include "sortTree.h"

extern char *recv_buffer[];
extern int recv_idx;

SortTree *SortTree_Init(char *key)
{
    SortTree *root = (SortTree *)malloc(sizeof(SortTree));
    memset(root->id, 0, sizeof(root->id));
    strcpy(root->id, key);
    root->left = NULL;
    root->right = NULL;
    return root;
}

void SortTree_insert(SortTree *root, char *key)
{
    SortTree *temp = root;
    SortTree *prev = NULL;
    while (temp != NULL)
    {
        prev = temp;
        if (strcmp(temp->id, key) > 0)
        {
            temp = temp->left;
        }
        else if (strcmp(temp->id, key) < 0)
        {
            temp = temp->right;
        }
        else
        {
            return;
        }
    }

    if (strcmp(prev->id, key) > 0)
    {
        prev->left = (SortTree *)malloc(sizeof(SortTree));
        memset(prev->left->id, 0, sizeof(root->id));
        strcpy(prev->left->id, key);
        prev->left->left = NULL;
        prev->left->right = NULL;
    }
    else
    {
        prev->right = (SortTree *)malloc(sizeof(SortTree));
        memset(prev->right->id, 0, sizeof(root->id));
        strcpy(prev->right->id, key);
        prev->right->left = NULL;
        prev->right->right = NULL;
    }
}

void SortTree_show(SortTree *root)
{
    if (root == NULL)
    {
        return;
    }
    SortTree_show(root->left);
    recv_buffer[recv_idx++] = root->id;
    // printf("%s ", root->id);
    SortTree_show(root->right);
}

int SortTree_delete(SortTree *root, SortTree *sortTree, char *key)
{
    if (sortTree == NULL)
    {
        return -1;
    }
    else
    {
        if (strcmp(sortTree->id, key) == 0)
        {
            SortTree *tempSortTree = prev_SortTree(root, sortTree, key);
            SortTree *temp = NULL;

            if (sortTree->right == NULL)
            {
                temp = sortTree;
                sortTree = sortTree->left;
                if (tempSortTree->left->id == temp->id)
                {
                    SortTree *free_SortTree = temp;
                    tempSortTree->left = sortTree;
                    free(free_SortTree);
                    free_SortTree = NULL;
                }
                else
                {
                    SortTree *free_SortTree = temp;
                    tempSortTree->right = sortTree;
                    free(free_SortTree);
                    free_SortTree = NULL;
                }
            }
            else if (sortTree->left == NULL)
            {
                temp = sortTree;
                sortTree = sortTree->right;
                if (tempSortTree->left->id == temp->id)
                {
                    SortTree *free_SortTree = temp;
                    tempSortTree->left = sortTree;
                    free(free_SortTree);
                    free_SortTree = NULL;
                }
                else
                {
                    SortTree *free_SortTree = temp;
                    tempSortTree->right = sortTree;
                    free(free_SortTree);
                    free_SortTree = NULL;
                }
            }
            else
            {
                temp = sortTree;

                SortTree *left_max = sortTree;
                left_max = left_max->left;
                while (left_max->right != NULL)
                {
                    temp = left_max;
                    left_max = left_max->right;
                }
                strcpy(sortTree->id, left_max->id);
                if (temp != sortTree)
                {
                    temp->right = left_max->left;
                    free(left_max);
                    left_max = NULL;
                }
                else
                {
                    temp->left = left_max->left;
                    free(left_max);
                    left_max = NULL;
                }
            }
        }
        else if (strcmp(key, sortTree->id) < 0)
        {
            SortTree_delete(root, sortTree->left, key);
        }
        else if (strcmp(key, sortTree->id) > 0)
        {
            SortTree_delete(root, sortTree->right, key);
        }
    }
}

SortTree *prev_SortTree(SortTree *root, SortTree *sortTree, char *key)
{
    if (root == NULL || sortTree == root)
    {
        return sortTree;
    }
    else
    {
        if (root->left != NULL && (strcmp(root->left->id, key) == 0))
        {
            return root;
        }
        else if (root->right != NULL && (strcmp(root->left->id, key) == 0))
        {
            return root;
        }
        else if (strcmp(key, root->id) < 0)
        {
            return prev_SortTree(root->left, sortTree, key);
        }
        else
        {
            return prev_SortTree(root->right, sortTree, key);
        }
    }
}