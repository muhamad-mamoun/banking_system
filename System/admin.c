/*
=============================================================================================================
Author       : Mamoun
Module       : 
File Name    : admin.c
Date Created : May 18, 2023
Description  : 
=============================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include <stdlib.h>
#include <string.h>
#include "admin.h"

/*===========================================================================================================
                                           < Global Variables >
===========================================================================================================*/

ClientRecordType* head_record = NULL;

/*===========================================================================================================
                                      < Private Functions Prototypes >
===========================================================================================================*/



/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : 
 * [Description]   : 
 * [Arguments]     : <>      -> 
 *                   <>      -> 
 * [return]        : The function returns void.
 ==========================================================================================================*/
TaskStateType CreateNewAccount(CLientAccountDataType* new_client_data)
{
	TaskStateType task_state;

	ClientRecordType new_record = (ClientRecordType*)(calloc(1,sizeof(ClientRecordType)));

	if(new_record != NULL)
	{
		new_record->record_data = *new_client_data;

		if(head_record != NULL)
		{
			new_record->next_record = head_record;
		}
		else
		{
			new_record->next_record = NULL;
		}

		head_record = new_record;
		task_state = DONE;
	}
	else
	{
		task_state = FAILED;
	}

	return task_state;
}

/*===========================================================================================================
 * [Function Name] :
 * [Description]   :
 * [Arguments]     : <>      ->
 *                   <>      ->
 * [return]        : The function returns void.
 ==========================================================================================================*/
TaskStateType CheckAccountBalance(unsigned long client_id, unsigned long* account_balance)
{
	TaskStateType task_state = FAILED;

	if(head_record != NULL)
	{
		ClientRecordType* current_record = head_record;

		while(current_record != NULL)
		{
			if(current_record->record_data->user_id == client_id)
			{
				*account_balance = current_record->record_data->account_balance;
				task_state = DONE;
				break;
			}

			current_record = current_record->next_record;
		}
	}

	return task_state;
}

/*===========================================================================================================
 * [Function Name] :
 * [Description]   :
 * [Arguments]     : <>      ->
 *                   <>      ->
 * [return]        : The function returns void.
 ==========================================================================================================*/
TaskStateType RemoveAccount(unsigned long client_id)
{
	TaskStateType task_state = FAILED;

	if(head_record != NULL)
	{
		ClientRecordType* current_record = head_record;
		while(current_record->next_record != NULL)
		{
			if(current_record->next_record->record_data->user_id == client_id)
			{
				ClientRecordType* freed_record = current_record->next_record;
				current_record->next_record = current_record->next_record->next_record;
				free(freed_record);
				task_state = DONE;
				break;
			}

			current_record = current_record->next_record;
		}
	}

	return task_state;
}
