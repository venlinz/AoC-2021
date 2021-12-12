// AOC-2021 part 2.
package main

import (
    "os"
    "log"
    "fmt"
    "flag"
    "bufio"
    "strings"
    "strconv"
)


func check(e error) {
    if e != nil {
        log.Fatal(e);
    }
}


func main() {
    var filepathString string;
    flag.StringVar(&filepathString, "filepath", "sample.txt", "filepath to input string");
    flag.Parse();

    filePtr, err := os.Open(filepathString);
    check(err);
    defer func() {
        fmt.Println("Closing the file");
        if err = filePtr.Close(); err != nil {
            log.Fatal(err);
        }
    }()
    
    var aim int64 = 0;
    var forward_distance int64 = 0;
    var depth int64 = 0;
    var num int = 0;
    fscanner := bufio.NewScanner(filePtr);
    for fscanner.Scan() {
        words := strings.Split(fscanner.Text(), " ");
        num, err =  strconv.Atoi(words[1]);
        check(err);
        if words[0][0] == 'u' {
            // fmt.Println(words[0]);
            // fmt.Println(words[1]);
            aim -= int64(num); 
        } else if words[0][0] == 'd' {
            aim += int64(num); 
        } else if words[0][0] == 'f' {
            forward_distance += int64(num);
            depth += aim * int64(num);
        }
    }
    err = fscanner.Err();
    check(err);
    fmt.Println("forward_distance: ", forward_distance);
    fmt.Println("depth: ", depth);
    fmt.Println("total: ", forward_distance * depth);
}
