# Отчет по лабораторной работе № 7
## по курсу "Объектно-ориентированное программирование"

Студент группы М8О-208Б-23 Соловьева Надежда Сергеевна

Работа выполнена 

Преподаватель: Иван Березуцкий

1. **Тема**: Ассинхронное программирование   
2. **Цель работы**:  
   • Знакомство с асинхронным программированием;  
   • Получение практических навыков в параллельной обработке данных;  
   • Получение практических навыков в синхронизации потоков.  

3. **Задание**: 
   Вариант 3:  
   Объекты: *"Орк, Белка, Медведь."*  
   Правило совместимости: *"Орки убивают медведей и орков. Медведи убивают белок. Белки не хотят воевать."*

   Общие требования:  
   - Размер карты: 100x100  
   - Мертвые NPC не передвигаются и не отображаются  
   - NPC не могут покинуть пределы карты  

   **Реализация 1 (Многопоточный)**:  
   - Реализация трех потоков:  
     1. Поток передвижения NPC и определения боевых столкновений  
     2. Поток проведения боев (механизм броска кубика)  
     3. Основной поток для отображения карты  
   - Контроль доступа к разделяемым ресурсам через std::shared_lock и std::lock_guard  
   - Контроль вывода через std::cout с помощью std::lock_guard  
   - Создание 50 NPC в случайных локациях при старте  
   - Остановка игры через 30 секунд с выводом списка выживших  

   **Реализация 2 (Coroutine)**:  
   - Реализация перемещения и сражений NPC в одном потоке с использованием coroutine  
   - Отображение карты в основном потоке  

4. **Код решения**:
   - [Многопоточная версия](main.cpp)  
   - [Версия с coroutine](main_pro.cpp)  

5. **Тестирование**: [Тесты](test/basic_tests.cpp)    

6. **Вывод**:   
В рамках лабораторной работы реализованы два подхода к управлению NPC:  
   - Многопоточный подход демонстрирует классическое разделение задач между потоками с использованием механизмов синхронизации;  
   - Подход с использованием корутин показывает более современный способ организации асинхронного выполнения задач.  
В процессе выполнения получили навыки в параллельной обработке данных и в синхронизации потоков.    
Личная оценка: 7/10. Было интересно, но очень муторно и под конец семестра вывозится чисто на морально-волевых.  