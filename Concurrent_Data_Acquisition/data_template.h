#ifndef TEMPLATE_H
#define TEMPLATE_H

// declare a template to store data from different sensors
template <typename T, size_t dimension>
struct data{
    size_t size;
    T (*data_)[dimension];
    data(size_t s);
    ~data();
};

#endif
