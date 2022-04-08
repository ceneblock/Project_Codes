template <typename T, size_t dimension>
data<T, dimension>::data(size_t s):size(s){
	data_ = new (nothrow) T[size][dimension];
		if(!data_){
			size = 0;
		}
}

template <typename T, size_t dimension>
data<T, dimension>::~data(){
	delete[] data_;
}

