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

fn correct_operation(target : i64, mut values : Vec<i64>) -> bool {
    let n : usize = values.len();
    // If only one element Check if correct!
    if n == 1 {
        return target == values[0];
    }
    // Find and remove last element
    let last_val = values[n-1];
    values.remove(n-1);
    // If multiplication
    let mut mul_ok : bool = false;
    if (target % last_val) == 0 {
        mul_ok = correct_operation(target/last_val, values.clone());
    }
    // Addition
    let add_ok = correct_operation(target-last_val, values.clone());

    return add_ok || mul_ok;
}

fn correct_operation_with_concat(target : i64, mut values : Vec<i64>) -> bool {
    let n : usize = values.len();
    // If only one element Check if correct!
    if n == 1 {
        return target == values[0];
    }
    // Find and remove last element
    let last_val = values[n-1];
    values.remove(n-1);
    // If multiplication
    let mut mul_ok : bool = false;
    if (target % last_val) == 0 {
        mul_ok = correct_operation_with_concat(target/last_val, values.clone());
    }
    // Addition
    let add_ok = correct_operation_with_concat(target-last_val, values.clone());
    // concat
    let mut tar_str : String = target.to_string();
    let val_str : String = last_val.to_string();
    let mut concat_ok : bool = false;
    if tar_str.ends_with(&val_str){
        println!("{}, {}",tar_str,val_str);
        tar_str.truncate(tar_str.len() - val_str.len());
        println!("{}", tar_str);
        if tar_str.len() == 0 {
            tar_str = String::from("0");
        }
        concat_ok = correct_operation_with_concat(tar_str.parse::<i64>().unwrap(), values.clone());
    }
    return add_ok || mul_ok || concat_ok;
}

fn main() -> std::io::Result<()>{
    let args: Vec<_> = env::args().collect();
    if args.len() <= 1 {
        return Ok(());
    }
    let mut file = File::open(args[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    let lines : Vec<&str> = split_lines(&contents);
    let problems : Vec<Vec<&str>> = lines.into_iter().map(|line| line.split(": ").collect()).collect();
    let mut ans_a: i64 = 0;
    let mut ans_b: i64 = 0;
    for problem in problems {
        let target : i64 = problem[0].parse::<i64>().unwrap();
        let values : Vec<i64> = problem[1].split(" ").map(|v| v.parse::<i64>().unwrap()).collect();
        println!("{} : {:?}", target, values);
        let correct = correct_operation(target, values.clone());
        println!("{}",correct);
        if correct {
            ans_a += target;
            ans_b += target;
        } else {
            let correct_b = correct_operation_with_concat(target, values.clone());
            println!("{}",correct_b);
            if correct_b {
                ans_b += target;
            }
        }
    }
    println!("Answer part A: {}", ans_a);
    println!("Anwer part B: {}", ans_b);
    Ok(())
}
