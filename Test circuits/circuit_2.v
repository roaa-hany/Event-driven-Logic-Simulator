`timescale 1ns / 1ps

module circuit_2(input a, input b, input c, output o);

    wire w1, bW1, nB;
    
    not #(2) (nB, b);
    and #(5) (w1, a, nB);
    buf #(1) (bW1, w1);
    nor #(7) (o, bW1, c);

endmodule
