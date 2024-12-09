use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;

fn split_lines(text: &str) -> Vec<str> {
    text
        .trim()
        .split_whitespace()
        .collect()
}

fn main() -> std::io::Result<()>{
    let args: Vec<_> = env::args().collect();
    if args.len() <= 1 {
        return Ok(());
    }
    let mut file = File::open(args[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    let lines = contents.split("\n");
    let mut vec1: Vec<i64> = Vec::new();
    let mut vec2: Vec<i64> = Vec::new();
    for line in lines {
        let numbers: Vec<_> = line.split("   ").collect();
        if numbers.len() > 1 {
            vec1.push(numbers[0].parse::<i64>().unwrap());
            vec2.push(numbers[1].parse::<i64>().unwrap());
        }
    }
    let mut ans_a: i64 = 0;
    let mut ans_b: i64 = 0;
    vec1.sort();
    vec2.sort();
    for (i, _el) in vec1.iter().enumerate() {
        println!("{} - {}", vec1[i], vec2[i]);
        ans_a += (vec1[i] - vec2[i]).abs();
    }
    println!("Answer part A: {}", ans_a);
    let mut ind_2: usize = 0;
    for (ind_1, _) in vec1.iter().enumerate() {
        let mut apps: i64 = 0;
        while vec2[ind_2] <= vec1[ind_1] {
            if vec2[ind_2] == vec1[ind_1] {
                apps += 1;
            }
            ind_2 += 1;
        }
        ans_b += vec1[ind_1] * apps;
    }
    println!("Anwer part B: {}", ans_b);
    Ok(())
}
