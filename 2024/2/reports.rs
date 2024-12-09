use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn print_vec(vec: &Vec<i64>) {
    for v in vec {
        print!("{} ", v);
    }
    print!("\n");
}

fn string_vec_to_int(string_vec: Vec<&str>) -> Vec<i64> {
    let mut int_vec: Vec<i64> = Vec::new();
    for s in string_vec {
        int_vec.push(s.parse::<i64>().unwrap());
    }
    return int_vec;
}

fn diff_vec(int_vec: Vec<i64>) -> Vec<i64> {
    let mut diff_vec: Vec<i64> = Vec::new();
    for i in 0..(int_vec.len()-1) {
        diff_vec.push(int_vec[i+1]-int_vec[i]);
    }
    return diff_vec;
}

fn correct_part_a(diff_vec: &Vec<i64>) -> bool {
    let dir: i64 = diff_vec[0];
    for d in diff_vec {
        if d.abs() < 1 || d.abs() > 3 {
            return false;
        } else if d*dir < 0 {
            return false;
        }
    }
    return true;
}

fn correct_part_b(diff_vec: &Vec<i64>) -> bool {
    if correct_part_a(diff_vec) {
        print_vec(diff_vec);
        return true;
    }
    for ind in 0..(diff_vec.len()+1) {
        let mut new_vec = diff_vec.clone();
        if ind == 0 {
            new_vec.remove(ind);
        } else if ind == diff_vec.len() {
            new_vec.remove(ind-1);
        } else {
            new_vec[ind-1] += new_vec[ind];
            new_vec.remove(ind);
        }
        if correct_part_a(&new_vec) {
            print_vec(&new_vec);
            return true;
        }
        
    }
    return false;
}

fn main() -> std::io::Result<()>{
    let args: Vec<_> = env::args().collect();
    if args.len() <= 1 {
        return Ok(());
    }
    let mut file = File::open(args[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    let lines: Vec<&str> = split_lines(&contents);
    
    let mut ans_a: i64 = 0;
    let mut ans_b: i64 = 0;
    for line in lines {
        let mut correct_a: bool = false;
        let mut correct_b: bool = false;
        
        let diff_vec: Vec<i64> = diff_vec(string_vec_to_int(line.split_whitespace().collect()));
        if correct_part_a(&diff_vec) {
            correct_a = true;
            ans_a += 1;
        }
        if correct_part_b(&diff_vec) {
            correct_b = true;
            ans_b += 1;
        }
        println!("{}, A: {}, B: {}",line, correct_a, correct_b);
    }
    println!("Answer part A: {}", ans_a);
    
    println!("Anwer part B: {}", ans_b);
    Ok(())
}
