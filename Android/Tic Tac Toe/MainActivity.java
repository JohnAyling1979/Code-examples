package edu.niu.cs.z981329.tictactoe;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.graphics.Color;
import android.graphics.Point;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.GridLayout;
import android.widget.TextView;

public class MainActivity extends Activity
{
    private Button[][] board;
    private TicTacToe game;
    private TextView gameStatus;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        //create game
        game = new TicTacToe();

        buildGUI();
    }//end of onCreate

    private void buildGUI()
    {
        //get screen width
        Point size= new Point();
        getWindowManager().getDefaultDisplay().getSize(size);

        //set button width
        int width = size.x/TicTacToe.SIDE;

        //Create gridlayout
        GridLayout gridLayout = new GridLayout(this);
        gridLayout.setRowCount(TicTacToe.SIDE + 1);
        gridLayout.setColumnCount(TicTacToe.SIDE);

        //fill board
        board = new Button[TicTacToe.SIDE][TicTacToe.SIDE];

        //create handler
        ButtonHandler buttonHandler = new ButtonHandler();


        for (int row =0;row<TicTacToe.SIDE;row++)
            for(int col=0;col<TicTacToe.SIDE;col++)
            {
                //create the button
                board[row][col] = new Button(this);

                //set the size
                board[row][col].setTextSize((int)(width*.25));

                //add listener
                board[row][col].setOnClickListener(buttonHandler);


                gridLayout.addView(board[row][col],width,width);
            }

        //add TV
        gameStatus = new TextView(this);

        //set up specs for TextView
        GridLayout.Spec rowSpec = GridLayout.spec(TicTacToe.SIDE,1);
        GridLayout.Spec colSpec = GridLayout.spec(0,TicTacToe.SIDE);

        //Create the layout parameters for the TextView
        GridLayout.LayoutParams params = new GridLayout.LayoutParams(rowSpec,colSpec);

        //apply the parameters to the TV
        gameStatus.setLayoutParams(params);

        //center the text
        gameStatus.setGravity(Gravity.CENTER);

        //set color of TV
        gameStatus.setBackgroundColor(Color.BLUE);

        //set width
        gameStatus.setWidth(width*TicTacToe.SIDE);

        //set the text size
        gameStatus.setTextSize((int)(width * 0.15));

        //set the text with the status
        gameStatus.setText(game.result());

        //add TV to the grid
        gridLayout.addView(gameStatus);

        //set the layout
        setContentView(gridLayout);
    }

    private class ButtonHandler implements View.OnClickListener
    {
        @Override
        public void onClick(View view)
        {
//            Toast.makeText(MainActivity.this,"Button Clicked"+view,Toast.LENGTH_SHORT).show();

            for (int row =0;row<TicTacToe.SIDE;row++)
                for(int col=0;col<TicTacToe.SIDE;col++)
                {
                    if(view==board[row][col])
                        update(row,col);
                }
        }
    }

    private void update(int row,int col)
    {
        if(game.play(row,col)==1)
        {
            board[row][col].setText("\u274C");

        }else
        {
            board[row][col].setText("\u2B55");
        }

        //check for end game
        if(game.isGameOver())
        {
            gameStatus.setBackgroundColor(Color.GREEN);
            enableButtons(false);
            gameStatus.setText(game.result());
            showNewGameDialog();
        }

    }

    public void showNewGameDialog()
    {
        //Create builder for the Dialog box
        AlertDialog.Builder alert = new AlertDialog.Builder(this);

        //set the title
        alert.setTitle("Game Over");

        //set message
        alert.setMessage("Play Again?");

        //set Yes button
        alert.setPositiveButton("Yes", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialogInterface, int i)
            {
                //resets the board
                game.resetGame();

                //turns the buttons back on
                enableButtons(true);

                //removes icons
                resetButtons();

                //update the status
                gameStatus.setBackgroundColor(Color.BLUE);
                gameStatus.setText(game.result());
            }
        });

        //set the No button
        alert.setNegativeButton("No", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialogInterface, int i)
            {
                MainActivity.this.finish();
            }
        });

        //display Dialog bos
        alert.show();
    }//end showNewGameDialog

    public void resetButtons()
    {
        for (int row =0;row<TicTacToe.SIDE;row++)
            for(int col=0;col<TicTacToe.SIDE;col++)
            {
                board[row][col].setText("");
            }
    }

    private void enableButtons(Boolean enabled)
    {
        for (int row =0;row<TicTacToe.SIDE;row++)
            for(int col=0;col<TicTacToe.SIDE;col++)
                board[row][col].setEnabled(enabled);
    }
}//end of MainActivity
