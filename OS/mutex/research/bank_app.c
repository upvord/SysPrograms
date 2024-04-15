#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  double balance;
  pthread_mutex_t lock;
} BankAccount;

// Function to deposit money into the bank account
void deposit(BankAccount *account, double amount) {
  pthread_mutex_lock(&account->lock);
  account->balance += amount;
  printf("Deposited $%.2f, New Balance: $%.2f\n", amount, account->balance);
  pthread_mutex_unlock(&account->lock);
}

// Function to withdraw money from the bank account
void withdraw(BankAccount *account, double amount) {
  pthread_mutex_lock(&account->lock);
  if (account->balance >= amount) {
    account->balance -= amount;
    printf("Withdrew $%.2f, New Balance: $%.2f\n", amount, account->balance);
  } else {
    printf("Failed to withdraw $%.2f, Insufficient funds: $%.2f\n", amount,
           account->balance);
  }
  pthread_mutex_unlock(&account->lock);
}

// Thread function for performing random transactions
void *perform_transactions(void *arg) {
  BankAccount *account = (BankAccount *)arg;
  for (int i = 0; i < 5; i++) {
    double amount = (rand() % 100) + 1;
    if (rand() % 2) {
      deposit(account, amount);
    } else {
      withdraw(account, amount);
    }
    sleep(1);
  }
  return NULL;
}

int main() {
  srand(time(NULL));
  BankAccount account = {1000.0,
                         PTHREAD_MUTEX_INITIALIZER}; // Initial balance of $1000
  pthread_t threads[10];

  // Creating multiple threads to perform transactions
  for (int i = 0; i < 2; i++) {
    pthread_create(&threads[i], NULL, perform_transactions, &account);
  }

  // Waiting for all threads to finish
  for (int i = 0; i < 2; i++) {
    pthread_join(threads[i], NULL);
  }

  // Cleanup
  pthread_mutex_destroy(&account.lock);

  printf("Final account balance: $%.2f\n", account.balance);
  return 0;
}
