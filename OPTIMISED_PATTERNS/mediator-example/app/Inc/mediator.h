#ifndef INC_MEDIATOR_H_
#define INC_MEDIATOR_H_

/* Forward declaration of Mediator */
typedef struct Mediator_t Mediator_t;

/* Mediator interface with a notify method */
typedef struct{
    void (*notify)(Mediator_t *mediator, const char *event);
}MediatorInterface_t;

/* base mediator structure */
struct Mediator_t {
    MediatorInterface_t *vtable;
};

typedef struct {
    Mediator_t base;
    /* References to colleague objects (opaque pointers) */
    void *light;
    void *thermostat;
    void *securitySystem;
};

#endif /* INC_MEDIATOR_H_ */