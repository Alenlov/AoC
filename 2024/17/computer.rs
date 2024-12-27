
use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::convert::TryInto;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

struct Computer {
    a: i64,
    b: i64,
    c: i64,
    instructions: Vec<usize>,
    pointer: usize,
    output: Vec<i64>,
}

impl Computer {

    fn combo(&self, op:usize) -> i64 {
        if op < 4 {
            return op as i64;
        } else if op == 4 {
            return self.a;
        } else if op == 5 {
            return self.b;
        } else if op == 6 {
            return self.c;
        } else {
            return -1;
        }
    }

    fn adv(&mut self, op: usize) {
        let base: i64 = 2;
        self.a = self.a / (base.pow(self.combo(op).try_into().unwrap()));
        self.pointer += 2;
    }

    fn bxl(&mut self, op: usize) {
        self.b = self.b^(op as i64);
        self.pointer += 2;
    }

    fn bst(&mut self, op: usize) {
        self.b = self.combo(op) % 8;
        self.pointer += 2;
    }

    fn jnz(&mut self, op: usize) {
        if self.a == 0 {
            self.pointer += 2;
        } else {
            self.pointer = op;
        }
    }

    fn bxc(&mut self, _op: usize) {
        self.b = self.b ^ self.c;
        self.pointer += 2;
    }

    fn out(&mut self, op: usize) {
        self.output.push( self.combo(op)%8 );
        self.pointer += 2;
        //println!("out: {}, A={}, B={}, C={}, p={}",(self.combo(op)%8),self.a,self.b,self.c,self.pointer);
    }

    fn bdv(&mut self, op: usize) {
        let base: i64 = 2;
        self.b = self.a / (base.pow(self.combo(op).try_into().unwrap()));
        self.pointer += 2;
    }

    fn cdv(&mut self, op: usize) {
        let base: i64 = 2;
        self.c = self.a / (base.pow(self.combo(op).try_into().unwrap()));
        self.pointer += 2;
    }

    fn run_program(&mut self, check: bool) {
        let mut halt: bool = false;
        self.pointer = 0;
        while !halt {
            if self.pointer >= self.instructions.len() {
                halt = true;
            } else {
                let code = self.instructions[self.pointer];
                let op = self.instructions[self.pointer+1];
                match code {
                    0 => self.adv(op),
                    1 => self.bxl(op),
                    2 => self.bst(op),
                    3 => self.jnz(op),
                    4 => self.bxc(op),
                    5 => self.out(op),
                    6 => self.bdv(op),
                    7 => self.cdv(op),
                    _ => return,
                }
                if check {
                    if code == 5 {
                        let n = self.output.len();
                        if self.output[n-1] != (self.instructions[n-1] as i64) {
                            return;
                        }
                    }
                }
            }
        }
    }

    fn find_smallest(&mut self) -> i64 {
        let mut poss_a: Vec<i64> = vec![0];
        let mut n : usize = 0;
        let inst_len = self.instructions.len();
        while n < inst_len {
            let mut new_a: Vec<i64> = Vec::new();
            let val_to_find: i64 = self.instructions[inst_len-1-n] as i64;
            for start_a in poss_a {
                for j in 0..8 {
                    self.pointer = 0;
                    self.a = start_a*8 + j;
                    self.b = 0;
                    self.c = 0;
                    self.output = Vec::new();
                    self.run_program(false);
                    if self.output[0] == val_to_find {
                        //println!("Hittade {} i offset {} från {}",val_to_find, j, start_a);
                        new_a.push(start_a*8 + j);
                    }
                }
            }
            poss_a = new_a;
            n += 1;
        }
        return *poss_a.iter().min().unwrap();
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
    let lines : Vec<&str> = split_lines(&contents);
    
    let a: i64 = ((lines[0].split(": ")).collect::<Vec<_>>())[1].parse::<i64>().unwrap();

    let inst: Vec<usize> = ((lines[4].split(": ")).collect::<Vec<_>>())[1].split(",").map(|i| i.parse::<usize>().unwrap()).collect();
    
    let mut comp: Computer = Computer{a:a, b:0, c:0, instructions:inst.clone(), pointer:0, output:Vec::new() };
    comp.run_program(false);
    let string_vec: Vec<String> = comp.output.into_iter().map(|i| i.to_string()).collect();
    println!("Answer part A: {}", string_vec.join(","));
    comp.output = Vec::new();
    let ans_b: i64 = comp.find_smallest();
    println!("Answer part B: {}", ans_b);
    Ok(())
}
