#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Bank account
typedef struct {
    char name[3]; 
    int balance;  
    pthread_mutex_t mutex; 
} Account;

// Transaction
typedef struct {
    char type[8];  
    char account[3]; 
    int amount;    
} Transaction;

// Client
typedef struct {
    char name[3]; 
    Transaction transactions[10]; 
    int transaction_count; 
} Client;

Account accounts[10]; 
int account_count = 0; 
Client clients[10];   
int client_count = 0;  

// Function to process transactions for a client
void* processTransactions(void* arg) {
    Client* client = (Client*)arg;
    for (int i = 0; i < client->transaction_count; i++) {
        Transaction* transaction = &client->transactions[i];
        for (int j = 0; j < account_count; j++) {
            // Find account
            if (strcmp(transaction->account, accounts[j].name) == 0) {
                pthread_mutex_lock(&accounts[j].mutex); 
                if (strcmp(transaction->type, "deposit") == 0) {
                    // Deposit
                    accounts[j].balance += transaction->amount; 
                } else if (strcmp(transaction->type, "withdraw") == 0 && accounts[j].balance >= transaction->amount) {
                    // Withdraw
                    accounts[j].balance -= transaction->amount;
                }
                pthread_mutex_unlock(&accounts[j].mutex); 
                break;
            }
        }
    }
    return NULL;
}

int main() {
    FILE* file = fopen("assignment_5_input.txt", "r");
    char line[50];

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "balance") != NULL) {
            sscanf(line, "%s balance %d", accounts[account_count].name, &accounts[account_count].balance);
            pthread_mutex_init(&accounts[account_count].mutex, NULL); 
            account_count++;
        } else {
            sscanf(line, "%s", clients[client_count].name);
            char* pos = strstr(line, clients[client_count].name) + strlen(clients[client_count].name);
            while (sscanf(pos, "%s %s %d", clients[client_count].transactions[clients[client_count].transaction_count].type, clients[client_count].transactions[clients[client_count].transaction_count].account, &clients[client_count].transactions[clients[client_count].transaction_count].amount) == 3) {
                clients[client_count].transaction_count++;
                pos = strstr(pos, clients[client_count].transactions[clients[client_count].transaction_count - 1].account) + strlen(clients[client_count].transactions[clients[client_count].transaction_count - 1].account);
            }
            client_count++;
        }
    }
    client_count--;
    
    fclose(file);

    pthread_t threads[client_count];

    // Threads for transactions
    for (int i = 0; i < client_count; i++) {
        pthread_create(&threads[i], NULL, processTransactions, &clients[i]);
    }

    // Wait for threads
    for (int i = 0; i < client_count; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("No. of Accounts: %d\nNo. of Clients: %d\n", account_count, client_count);

    for (int i = 0; i < account_count; i++) {
        printf("%s balance %d\n", accounts[i].name, accounts[i].balance);
    }

    return 0;
}