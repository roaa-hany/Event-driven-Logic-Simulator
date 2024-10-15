`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/14/2024 12:56:15 PM
// Design Name: 
// Module Name: circuit_3
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module circuit_3(

    );
    input A,B,C;
    output out;
    wire w1, w2;
    and(w1, A,B);
    not(w2, C);
    xor(out,w1,w2);
endmodule
