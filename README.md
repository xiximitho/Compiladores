# Análisador

Projeto utilizando a api GTK4.0 (binding de c++ gtkmm-4.0), que consiste em ser um analisador léxico e sintático.
(EM BREVE TABELA DE SIMBOLOS E TOKENS)

### 📋 Pré-requisitos
É necessário o uso da ferramenta CMake e Make utilizando o CLang ou GCC para a instalação.

O projeto foi construido utilizando a api gtkmm-4.0 junto há glibmm e sigc++, instale de acordo com sua distro. <br>
```
Ubuntu: apt-get install libgtkmm-4.0-dev cmake make clang
```
```
Manjaro: pamac install gtkmm-4.0 cmake make clang 
```
```
Fedora: dnf install gtkmm4.0-devel cmake make clang 
```

### 🔧 Instalação

1. Clone o repostório
   ```sh
   git clone https://github.com/xiximitho/Compiladores.git
   ```
2. Crie a pasta em que será realizado a compilação.
   ```sh
   cd Compiladores && mkdir build && cd build
   ```
3. Gere os arquivos para realização do Make e Make install (CMake sempre pega o diretório atual para geração)
   ```sh
   cmake ..
   ```   
4. Compilação dos arquivos
   ```sh
   make && make install
   ```
