#include "blocking_queue.h"

void BlockingQueueInit(BlockingQueue* q, int elem_size, void (*free_fn)(void*)){
    StackInit(&q->s, elem_size, free_fn);
    pthread_mutex_init(&q->lock, NULL); 
    pthread_cond_init(&q->cond, NULL);
}

void BlockingQueueDestroy(BlockingQueue* q){
    StackDispose(&q->s);
    pthread_mutex_destroy(&q->lock);
    pthread_cond_destroy(&q->cond) ;
}

void BlockingQueueAdd(BlockingQueue* q, void* value_ptr){
    pthread_mutex_lock(&q->lock);
    StackPush(&q->s, value_ptr); // amis dacva gvinda kakras ro atomurad moxdes chamateba
    // pthread_cond_broadcast(&q->cond); // agvidzebs yvela conds rac gvaq da problema isaa ro 
    // 10 cali get ro mqondes gamodzaxebuli cariel stack ze da aq erti elementis add is mere
    // yvela signali gavagvidzo cariel stackidan ecdebian gets da daiqrasheba
// --------------------------------------------------------------------------------------------------  
    // pthread_cond_signal(&q->lock);  // es yoveltvis imushavebs mara minusi aq
    // anu tu stackshi gvaq elementebi elemsize > 0ze mashin signals azri ar aq imitoro
    // sleepze ar iqneba ro gaagvidzos. egaa erti minusi
// --------------------------------------------------------------------------------------------------    
    // if(q->s.log_len == 1) pthread_cond_signal(&q->cond); // aq raari problema:
    // mag 10 get maq gamodzaxebuli da mere 3 add. size = 0. ise sheieleba moxdes ro 
    // signal mxolod ertxel iqnas gamodzaxebuli. da loglen 2 chaiweros. signalebis dakargva sheileba moxdes
// --------------------------------------------------------------------------------------------------
    if(q->s.log_len == 1) pthread_cond_broadcast(&q->cond); // aq kide problema ari ro
    // tu 1 elementris chamateba minda loglen 1 gaxdeba da getebi ari gamodzaxebuli yvela gaigvidzebs
    // erti elementis wasashlkelad da sheileba cariel satckshi geti sgamodzaxeba cadon amitom 
    // get shi shesacvlelia if(loglen == 0) kiara while gvinda ro amowmmons ra xelaxla tu vinmem daaswro
    // isev daidzinon.
    pthread_mutex_unlock(&q->lock);
}

void BlockingQueueGet(BlockingQueue* q, void* value_ptr){
    pthread_mutex_lock(&q->lock);
    // if(q->s.log_len == 0){
    while(q->s.log_len == 0){   
        //wait vqnat ro piroba davicvat  da magistvis gamoviyenebt cond-s.
        pthread_cond_wait(&q->cond, &q->lock); // dalockil mutexshi vart exla da cond wait ras izavs
        // ro daidzinebs tviton da amavdroulad locks gaxsnis unlocks izavs ro add shi shedzlon shignit
        // shesvla da signalis gadacema 
        /*
            1. register on cond
            2. unlock mutex
             .... wait for signal
             ....
            3. lock mutex
            4.return
        */
    }
    StackPop(&q->s, value_ptr); // amis dacva gvinda kakras ro atomurad moxdes amogdeba
    pthread_mutex_unlock(&q->lock);
}