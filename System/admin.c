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

static ClientRecordType* head_record = NULL;

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
TaskStateType RemoveAccount(unsigned long client_id)
{
	TaskStateType task_state = FAILED;

	if(head_record != NULL)
	{
		ClientRecordType* current_record = head_record;
		while(current_record->next_record != NULL)
		{
			if(current_record->next_record->record_data->client_id == client_id)
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

ClientRecordType* FindClientAccount(unsigned long target_client_id)
{
	ClientRecordType* target_client_record = NULL;

	if(head_record != NULL)
	{
		ClientRecordType* current_record = head_record;
		while(current_record != NULL)
		{
			if(current_record->record_data->client_id == target_client_id)
			{
				target_client_record = current_record;
				break;
			}

			current_record = current_record->next_record;
		}
	}

	return target_client_record;
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
		ClientRecordType* target_client_record = FindClientAccount(client_id);

		if(target_client_record != NULL)
		{
			*account_balance = target_client_record->record_data->account_balance;
			task_state = DONE;
		}
	}

	return task_state;
}

TaskStateType MakeTransaction(unsigned long sender_id, unsigned long receiver_id, unsigned long transaction_value)
{
	TaskStateType task_state = FAILED;

	ClientRecordType* sender_client_record = FindClientAccount(sender_id);
	ClientRecordType* receiver_client_record = FindClientAccount(receiver_id);

	if((sender_client_record != NULL) && (receiver_client_record != NULL))
	{
		receiver_client_record->record_data->account_balance += transaction_value;
		sender_client_record->record_data->account_balance -= transaction_value;
		task_state = DONE;
	}

	return task_state;
}

TaskStateType DepositMoney(unsigned long client_id, unsigned long deposit_value)
{
	TaskStateType task_state = FAILED;

	ClientRecordType* client_record = FindClientAccount(client_id);

	if(client_record != NULL)
	{
		client_record->record_data->account_balance += deposit_value;
		task_state = DONE;
	}

	return task_state;
}

TaskStateType WithdrawMoney(unsigned long client_id, unsigned long Withdraw_value)
{
	TaskStateType task_state = FAILED;

	ClientRecordType* client_record = FindClientAccount(client_id);

	if(client_record != NULL)
	{
		client_record->record_data->account_balance -= Withdraw_value;
		task_state = DONE;
	}

	return task_state;
}
