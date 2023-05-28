#include "sp_data_queue.h"

/*
Serial Port thought process:

Receiving a byte: When data comes in, it first goes into the Receiver Buffer Register (RBR). Before you fetch it from there, you check the Line Status Register (LSR) to see if data is available (Receiver Data Available bit) and if there were any errors (like parity error, framing error, etc.) while receiving the data. If everything is fine according to LSR, you then read the byte from RBR.

Sending a byte: Before sending a byte, you first check the LSR to see if the Transmitter Holding Register (THR) is empty. If it is, you can then put your byte into THR from where it will be transmitted.

Handling interrupts: When an interrupt happens, your interrupt handler gets triggered. It keeps reading the incoming data and pushing it into a queue as long as there is incoming data and the queue isn't full. This is because data might come in faster than you can process it. So, instead of processing the byte right away, you push it into a queue from where it can be processed later at a suitable pace.

This queue mechanism allows the system to handle data bursts where lots of data may come in quickly, and it can then be processed at a pace that the system can handle, ensuring that no data gets lost or missed.

he frequency of errors depends largely on the quality of your transmission medium and the accuracy of your transmitting and receiving devices. Here's a brief on each error:

Parity Error: Occurs when the parity bit of a received byte does not match the calculated parity. It's used for error detection. Parity errors might occur due to noise on the line or problems with the transmitting device.

Character Overwritten / Overrun Error: Occurs when the receiving software is too slow to handle incoming data and the incoming data overwrites an unread character in the receiver's buffer. It might occur if the receiver cannot process incoming data as fast as it arrives.

Framing Error: Occurs when the receiver does not see a valid STOP bit where it is expected. This could occur due to a mismatch in the transmission speed (baud rate) between the sender and receiver, or noise on the line.

In most systems, overrun errors might be the most frequent if the system isn't capable of handling the incoming data quickly enough. However, this would be heavily dependent on the specific hardware and software configuration, the load the system is under, and the quality of the transmission medium. Noise or faulty hardware could lead to increased parity or framing errors. Therefore, it's difficult to categorically state which error would occur most without more specific context.

In simpler terms:

Para receber um byte:
Lês o LSR para ver se tens o receiver data available
Se tiveres, verificas se houve erro de paridade e os outros três erros do lsr
Se estiver tudo em ordem no lsr (status register), significa que tens um byte para ler
Por isso vais ao RBR buscá-lo
Quando a info é recebida ela vai diretamente para o rbr
E recebes um "relatório" sobre a informação no lsr a dizer se tá estragada ou não
Nos slides aconselham a não processar logo o byte porque ele manda byte a byte
Se mandar MTA cena ao mesmo tempo não há tempo para processar tudo
Por isso das push da info para a queue e depois tratas a informação
O send byte é a mm cena
Como tás a mandar não precisas de ver erro de paridade
Só vais ao lsr para ver se o thr está vazio (transmiter holder register), que é o mesmo que o receiver buffet register
O interrupt handler dá handle as interrupções. Enquanto a queue não estiver cheia e enquanto eu estiver a receber informação
Vai meter todos os dados que recebe para a queue
*/

DataQueue* data_queue_init() {
    DataQueue* dq = (DataQueue*)malloc(sizeof(DataQueue));
    if(dq == NULL) {
        perror("Unable to allocate memory for DataQueue");
        exit(EXIT_FAILURE);
    }
    dq->max_capacity = 100; //max capacity of the queue for now. might change later
    dq->head = dq->queue_size = 0;
    dq->tail = 99; //
    dq->elements = (int*)malloc(dq->max_capacity * sizeof(int));
    return dq;
}

void data_queue_destroy_queue(DataQueue* dq) {
    free(dq->elements);
    free(dq);
}

bool data_queue_push(DataQueue* dq, uint8_t data){
    if (data_queue_is_full(dq)) return false;
    dq->tail = (dq->tail + 1) % dq->max_capacity;
    dq->elements[dq->tail] = data;
    dq->queue_size++;
    return true;
}

uint8_t data_queue_pop(DataQueue* dq){
    if (data_queue_is_empty(dq)) return 0;
    int element = dq->elements[dq->head];
    dq->head = (dq->head + 1) % dq->max_capacity;
    dq->queue_size--;
    return element;
}

int data_queue_current_size(DataQueue * dq){
    return dq->queue_size;
}

//returns the next element in the queue without removing it
uint8_t data_queue_peek(DataQueue* dq) {
    if (data_queue_is_empty(dq))
        return 0;
    return dq->elements[dq->head];
}

bool data_queue_contains(DataQueue* dq, uint8_t element) {
    for (int i = dq->head; i != dq->tail; i = (i + 1) % dq->max_capacity) {//The modulo operation ensures that i stays within the bounds of the array, giving the circular behavior
        if (dq->elements[i] == element)
            return true;
    }
    return false;
}

uint8_t data_queue_front(DataQueue* dq){
    if (data_queue_is_empty(dq)) return 0;
    return dq->elements[dq->head];
}

uint8_t data_queue_back(DataQueue* dq){
    if (data_queue_is_empty(dq)) return 0;
    return dq->elements[dq->tail];
}

bool data_queue_is_full(DataQueue* dq){
    return (dq->queue_size == (int) dq->max_capacity);
}

bool data_queue_is_empty(DataQueue* dq){
    return (dq->queue_size == 0);
}
