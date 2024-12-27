use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use regex::Regex;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn solution(vals : (i128,i128,i128,i128,i128,i128)) -> i128{
    let (a,b,c,d,e,f) = vals;
    let det : i128 = a*d - b*c;
    if det == 0 {
        println!("No inverse! Warning!");
        return 0; //no solution
    }
    let a_sol = d*e - c*f;
    let b_sol = a*f - b*e;
    if (a_sol % det == 0) && (b_sol % det == 0) {
        return 3*(a_sol/det) + (b_sol/det);
    } else {
        return 0;
    }
}


fn main() -> std::io::Result<()>{
    let args: Vec<_> = env::args().collect();
    if args.len() <= 1 {
        return Ok(());
    }
    let mut file = File::open(args[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    contents = contents.trim().to_string();
    let lines : Vec<&str> = split_lines(&contents);

    let re_a = Regex::new(r"Button A: X\+(\d+), Y\+(\d+)").unwrap();
    let re_b = Regex::new(r"Button B: X\+(\d+), Y\+(\d+)").unwrap();
    let re_p = Regex::new(r"Prize: X=(\d+), Y=(\d+)").unwrap();


    let mut ans_a : i128 = 0;
    
    let mut ans_b : i128 = 0;

    let mut a : i128 = 0;
    let mut b : i128 = 0;
    let mut c : i128 = 0;
    let mut d : i128 = 0;
    let mut e : i128;
    let mut f : i128;

    for line in lines {
        if re_a.is_match(line) {
            let (_, [x,y]) = re_a.captures(line).unwrap().extract();
            a = x.parse::<i128>().unwrap();
            b = y.parse::<i128>().unwrap();
        } else if re_b.is_match(line) {
            let (_, [x,y]) = re_b.captures(line).unwrap().extract();
            c = x.parse::<i128>().unwrap();
            d = y.parse::<i128>().unwrap();
        } else if re_p.is_match(line) {
            let (_, [x,y]) = re_p.captures(line).unwrap().extract();
            e = x.parse::<i128>().unwrap();
            f = y.parse::<i128>().unwrap();
            ans_a += solution((a,b,c,d,e,f));
            e += 10000000000000;
            f += 10000000000000;
            ans_b += solution((a,b,c,d,e,f));
        }
    }
    
    println!("Answer part A: {}", ans_a);
    println!("Anwer part B: {}", ans_b);
    Ok(())
}
