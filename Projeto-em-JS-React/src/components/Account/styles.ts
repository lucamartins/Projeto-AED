import styled from 'styled-components';

export const LoginContainer = styled.div`
    position: fixed;
    top:0;
    bottom:0;
    right:0;
    left:0;
    background: var(--blue);
    display: flex;
    align-items: center;
    justify-content: center;
`
interface LoginContainerProps{
    isWrong: boolean;
    isCpfWrong: boolean;
}

export const LoginForm = styled.form<LoginContainerProps>`
    display: flex;
    flex-direction: column;
    width:100%;
    max-width: 600px;
    background: var(--background);
    padding: 3rem;
    position: relative;
    border-radius: 0.24rem;

    h2{
        color: var(--text-title);
        font-size: 1.5rem;
        margin-top: 2rem;
        margin-bottom: 2rem;
    }

    input{
        width:100%;
        padding: 0 1.5rem;
        height: 4rem;
        border-radius: 0.25rem;
        border: 1px solid ${(props)=>props.isCpfWrong? 'red' : '#d7d7d7'};
        background: #e7e9ee;

        font-weight:400;
        font-size:1rem;

        &::placeholder{
            color: ${(props)=>props.isCpfWrong? 'red' : 'var(--text-body)'}
        }

        & + input{
            margin-top: 1rem;
        }

        &.senha{
            border: 1px solid ${(props)=>props.isWrong? 'red' : '#d7d7d7'};

            &::placeholder{
                color: ${(props)=>props.isWrong? 'red' : 'var(--text-body)'}
            }
        }

    }

    button{
        width: 100%;
        padding: 0 1.5rem;
        height: 4rem;
        background: var(--green);
        color: #fff;
        border-radius: 0.25rem;
        border:0;
        font-size:1rem;
        font-weight:600;
        margin-top: 1.5rem;

        transition: filter 0.2s;

        & + button{
            margin-top: 0.5rem;
        }

        &:hover{
            filter: brightness(0.9);
        }

    }
`