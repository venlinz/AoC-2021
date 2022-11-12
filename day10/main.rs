// my rusty rust programs.
use std::{fs::File, io::Read};
use std::collections::HashMap;


#[derive(Debug)]
struct Stack {
    data: Vec<char>,
}

impl Stack {
    fn new() -> Stack {
        return Stack {
            data: Vec::new()
        };
    }

    fn push(&mut self, c: char) {
        self.data.push(c);
    }

    fn pop(&mut self) -> char {
        self.data.pop().unwrap()
    }

    fn top(&self) -> char {
        return *self.data.last().unwrap();
    }

    fn get_vec(&self) -> &Vec<char> {
        return &self.data;
    }
}

fn calc_second_problem_score(v: &&Vec<char>) -> u64 {
    let points = HashMap::from([
        ('(', 1),
        ('[', 2),
        ('{', 3),
        ('<', 4),
    ]);
    let mut single_line_score: u64 = 0;
    for symbol in v.iter().rev() {
        single_line_score *= 5;
        single_line_score += points.get(symbol).unwrap();
    }
    return single_line_score;
}

fn main() -> std::io::Result<()> {
    let pairs = HashMap::from([
        ('(', ')'),
        ('[', ']'),
        ('{', '}'),
        ('<', '>'),
    ]);
    let points = HashMap::from([
        (')', 3),
        (']', 57),
        ('}', 1197),
        ('>', 25137),
    ]);
    let example_file = "./src/input.txt";
    let mut file = File::open(example_file)?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    let lines: Vec<&str> = contents.split('\n').collect();
    let mut score: usize = 0;

    let mut scores: Vec<u64> = Vec::new();
    for line in lines {
        if line.is_empty() {
            continue;
        }
        let mut stack = Stack::new();
        let mut is_invalid = false;
        for c in line.trim().chars() {
            if pairs.contains_key(&c) {
                stack.push(c);
            } else if *pairs.get(&stack.top()).unwrap() != c {
                score += points.get(&c).unwrap();
                is_invalid = true;
                break;
            } else {
                stack.pop();
            }
        }
        if !is_invalid {
            scores.push(calc_second_problem_score(&stack.get_vec()));
        }
    }
    println!("the first answer is {}", score);
    scores.sort();
    println!("the second answer: {}", scores.get(scores.len() / 2).unwrap());

    Ok(())
}
