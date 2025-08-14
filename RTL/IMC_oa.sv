// The following module you see before you receives a clock and
// has a synchronous reset. The reset is active high. 

// Extend the module you have been given to drive out_valid,
// out_trigger, and out_header as described in the challenge
// description. You may add or remove code but please do NOT modify
// the module ports. The testbench provided will tell you when you
// have correctly done this. We are looking for the test to pass
// first and foremost.

// You have the ability to view or download the waveform produced
// by the design. You can also synthesize the design. Be aware
// this can take a few minutes to run.


module top (
    input logic                       clk,
    input logic                       reset,

    input logic                       in_valid,
    input logic [15:0]                in_data,

    output logic                      out_valid,
    output logic                      out_trigger,
    output logic [31:0]               out_header
);
    //FSM state definitions
    localparam STATE_IDLE = 1'b0;
    localparam STATE_SEQUENCE = 1'b1;
    
    logic state, next_state;
    
    //reg definitions for header/payloads
    logic [31:0] header; //one common reg for all headers 
    logic [23:0] payload_1;
    logic [23:0] payload_2;
    logic [23:0] payload_3;
    logic [23:0] payload_4; 
    
    //feed counter and sequence counter
    logic [3:0] sequence_count;
    
    localparam logic [23:0] MATCH_DATA_1 = 24'hDF0132;
    localparam logic [23:0] MATCH_DATA_2 = 24'h4DE91B;
    localparam logic [23:0] MATCH_DATA_3 = 24'h73AC06;
    localparam logic [7:0] MATCH_DATA_4 =   8'hA1;
    
    //FSM state transition logic
    always @(*) begin
        case(state)
            STATE_IDLE: begin
                if(in_valid)
                    next_state = STATE_SEQUENCE;
                else
                    next_state = STATE_IDLE;
            end
            STATE_SEQUENCE: begin
                if(sequence_count == 4'd8) //full seq. processed
                    next_state = STATE_IDLE;
                else 
                    next_state = STATE_SEQUENCE;
            end
            default: next_state = STATE_IDLE;
        endcase
    end
            
    //FSM state output logic
    always @(posedge clk or posedge reset) begin
        if(reset) begin
            out_valid <= 1'b0;
            out_trigger <= 1'b0;
            out_header <= 32'b0;
            
            header <= 32'b0;
            payload_1 <= 24'b0;
            payload_2 <= 24'b0;
            payload_3 <= 24'b0;
            payload_4 <= 24'b0;
            
            sequence_count <= 4'b0;
        end
        else begin
            case(next_state)
                STATE_IDLE: begin
                   out_trigger <= 1'b0;
                   out_valid <= 1'b0;
                   out_header <= 32'b0;
               
                   header <= 32'b0;
                   payload_1 <= 24'b0;
                   payload_2 <= 24'b0;
                   payload_3 <= 24'b0;
                   payload_4 <= 24'b0;
                    
                   sequence_count <= 4'b0;
                end
                STATE_SEQUENCE: begin
                    if(in_valid)begin
                        sequence_count <= sequence_count + 1'b1;
                        case(sequence_count)
                            4'd0:begin
                                header[7:0] <= in_data[15:8];
                                payload_1[23:16] <= in_data[7:0]; 
                            end
                            4'd1:begin
                                payload_1[15:0] <= in_data;
                            end
                            4'd2:begin
                                header[15:8] <= in_data[15:8];
                                payload_2[23:16] <= in_data[7:0];
                            end
                            4'd3:begin
                                payload_2[15:0] <= in_data;
                            end
                            4'd4:begin
                                header[23:16] <= in_data[15:8];
                                payload_3[23:16] <= in_data[7:0];
                            end
                            4'd5:begin
                                payload_3[15:0] <= in_data;
                            end
                            4'd6:begin
                                header[31:24] <= in_data[15:8];
                                payload_4[23:16] <= in_data[7:0];
                            end
                            4'd7:begin 
                                out_valid <= 1'b1;
                                out_header <= header;
                                out_trigger <= ((payload_1 == MATCH_DATA_1) && 
                                                (payload_2 == MATCH_DATA_2) &&
                                                (payload_3 == MATCH_DATA_3) && 
                                                (payload_4[23:16] == MATCH_DATA_4) &&
                                                (in_data == 16'hC47D));

                            end
                            default: sequence_count <= sequence_count;
                       endcase                     
                    end
                end
            endcase
        end
    end
    
    //FSM state transition logic
    always @(posedge clk or posedge reset) begin
        if(reset) begin
            state <= STATE_IDLE;
        end
        else begin
            state <= next_state;
        end
    end

endmodule