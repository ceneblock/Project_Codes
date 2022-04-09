#ifndef TEMPLATE_H
#define TEMPLATE_H

// declare a template with variable dimensions to store datafrom different sensors
template <typename T, size_t dimension>
struct data{
    size_t size;
    T (*data_)[dimension];
    data(size_t s);
    ~data();
};

#endif
