#include <zephyr/kernel.h>

#define STACK_SIZE 1024
#define THREAD_PRIORITY 5
#define CAPACIDADE_VITRINE 10

static volatile int saldo_vitrine;

K_THREAD_STACK_DEFINE(padeiro_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(cliente_stack, STACK_SIZE);
static struct k_thread padeiro_data;
static struct k_thread cliente_data;

static void padeiro(void *arg1, void *arg2, void *arg3)
{
	int paes_produzidos = 0;

	ARG_UNUSED(arg1);
	ARG_UNUSED(arg2);
	ARG_UNUSED(arg3);

	while (1) {
		k_msleep(2000);

		if (saldo_vitrine < CAPACIDADE_VITRINE) {
			paes_produzidos++;
			saldo_vitrine++;
			printk("PADEIRO: Pão #%d pronto (Saldo vitrine = %d)\n",
			       paes_produzidos, saldo_vitrine);
		} else {
			printk("PADEIRO: Vitrine cheia (Saldo vitrine = %d)\n",
			       saldo_vitrine);
		}
	}
}

static void cliente(void *arg1, void *arg2, void *arg3)
{
	int paes_consumidos = 0;

	ARG_UNUSED(arg1);
	ARG_UNUSED(arg2);
	ARG_UNUSED(arg3);

	while (1) {
		k_msleep(500);

		if (saldo_vitrine > 0) {
			paes_consumidos++;
			saldo_vitrine--;
			printk("CLIENTE: Peguei pão #%d (Saldo vitrine = %d)\n",
			       paes_consumidos, saldo_vitrine);
		} else {
			printk("CLIENTE: Vitrine vazia (Saldo vitrine = %d)\n",
			       saldo_vitrine);
		}
	}
}

int main(void)
{
	k_thread_create(&padeiro_data, padeiro_stack, STACK_SIZE,
			padeiro, NULL, NULL, NULL,
			THREAD_PRIORITY, 0, K_NO_WAIT);

	k_thread_create(&cliente_data, cliente_stack, STACK_SIZE,
			cliente, NULL, NULL, NULL,
			THREAD_PRIORITY, 0, K_NO_WAIT);

	return 0;
}
