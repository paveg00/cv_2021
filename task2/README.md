В библиотеке `CPP_Medianfilter/lib/` реализованы требуемые функции 
Чтобы запустить ноутбук нужно создать `venv` окружение из `python_packages/requirments.txt`


Включение в jupyter notebook
`python -m ipykernel install --user --name=cvenv`

Скомпилировать библиотеку с Cython, чтобы использовать python обертку:
`python setup.py build_ext --inplace`