# Doxygen tutorial 41047025S 王重鈞

## Introduction:
Doxygen is a file gnerate tool. It helps specific format annotation turn into description file. The progammer can read the file and understand a funcion, file, struct meaning in a brief time. Reduce waste time to read the code.

## How to download

You can use `sudo apt install doxygen` to install on terminal, or you can follow below steps.

### GIT repository

If you want to download by git repository, only following below operations.

First, you need install g++, python, cmake, flex, bison.
Then, use these command.
```
$ git clone https://github.com/doxygen/doxygen.git
$ cd doxygen  
$ mkdir build  
$ cd build
$ cmake -G "Unix Makefiles\" ..
$ make
```

If you want to download binary, you can search their website.
[DOWNLOAD WEB](https://doxygen.nl/download.html)

## Configuration

If we want to output file meet the format which we want, we need to set the Configuration to our expection.

1. Generate Configuration file

    Use `doxygen -g <config_file>` to generate the Configuration file.

2. Change the setting.  
    Then, you can revise `<config_file>` argument to let the output meet your demand.
    Here is offical document for configuration.
    [CONFIGURATION LIST](https://doxygen.nl/manual/config.html)

<div style="page-break-after: always;"></div>

## Write annotation

After download doxygen, we need to write format annotation in your code let doxygen can read it.

1. Annotation text need be included by following types annotation marks

    ```
    /**
     * ... text ...
     */
    ```

    ```
    /*!
     * ... text ...
     */
    ```

    ```
    /*!
     ... text ...
    */
    ```

    ```
    ///
    /// ... text ...
    ///
    ```

    ```
    //!
    //!... text ...
    //!
    ```

    ```
    /////////////////////////////////////////////////
    /// ... text ...
    /////////////////////////////////////////////////
    ```

    ```
    /************************************************
     *  ... text
     ***********************************************/
    ```
    All of them are vaild.

<div style="page-break-after: always;"></div>

2. Write annotation text

    For general, the annotaion be used to describe a function or class. Thus, we usually have a brief description and detail description for function and class. 
    
    Thus, Doxygen will view the first line of annotation is brief description, and after a blank line, following text will be view asd etail description.
    ```
    /**
         brief description

         detail description
         .
         .
    */
    ```

    However, there's another way can tag annotaion more clear. That is use `command`.
    

    In doxygen, you can use `@` or ``\``<commnand> to tag the annotaions. For, instace, we can use `\brief <text>` to tag text is a brief annotation for this function.
    
    Beside, there're other function command you can use, here is an example.
    
     ```
    /** \file myfile.h
         \brief description
         \var a is 5

         detail description
         .
         .
    
         \author Takala
    */
    ```
    
     Here is offical document for command.
    [COMMAND LIST](https://doxygen.nl/manual/commands.html)

<div style="page-break-after: always;"></div>

## Generate the file
    
First, use following command.
    
`doxygen <config>`

Then we will get two directories, html and latex.

* In html, you can find a file`index.html`, click it and you can read description file on website.
    
* In latex, you can use makefile to build the pdf file.
    If you don't have `texlive-latex`, 
    you can use 
    `sudo apt-get install texlive-latex-base`
    `sudo apt-get install texlive-latex-extra` 
    to downlaod.
    And the output pdf will named as `refman.pdf`

## Example
    
In example.c, use could find I have written some annotations in code file.
    
Then, use can use `make` to build `refman.pdf` and read the result.
