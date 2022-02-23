# IF684-Ativ2
Construção de um agente autonomo simples usando SFML https://www.sfml-dev.org/index.php
## Instruções
### Em Linux Ubuntu 18.04 ou mais recente 
#### Caso já tenha SFML instalado: 
- É preciso apenas fazer: 
``` 
    make compile
    make run
``` 
#### Caso não tenha o SFML, instale rodando:
```
    sudo apt-get install build-essential
    sudo apt-get install libsfml-dev

```
### Em caso de outros sistemas operacionais:
- Instale o SFML (MacOS: https://www.sfml-dev.org/tutorials/2.5/start-osx.php , Windows: https://www.sfml-dev.org/tutorials/2.5/start-vc.php ) e compile usando 
``` 
    make compile
    make run
``` 
- É importante ressaltar que é preciso que se tenha o CMake instalado