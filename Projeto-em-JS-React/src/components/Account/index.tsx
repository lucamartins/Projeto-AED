import { useState } from 'react'
import Modal from 'react-modal';
import logo1Img from '../../assets/logo1.svg'

import { LoginForm, LoginContainer, SignUp} from './styles'

Modal.setAppElement('#root');
interface Transaction{
    title: string,
    amount: number,
    type: string,
    category: string,
    createdAt: Date,
}

interface AccountProps{
    cpf: string,
    name: string,
    password : string,
    transactions : Transaction[]
}

export function  Account() { 
    const [ isTransactionModalOpen, setIsTransactionModalOpen ] = useState(false);
    const [ password, setPassword ] = useState('');
    const [ createBool, setCreateBool ] = useState(false);
    const [ isPasswordWrong, setIsPasswordWrong ] = useState(false);
    const [ isCpfWrong, setIsCpfWrong ] = useState(false);
    const [ step, setStep ] = useState(3);
    const [ cpf, setCpf] = useState('');

    if(step===1){
        return(
            <>
                <LoginContainer>
                    <LoginForm isWrong={isPasswordWrong} isCpfWrong={isCpfWrong}>
                        <img src={logo1Img} alt="AJL Bank"/>
                        <h2>Olá, Seja bem vindo</h2>
                        <input placeholder={isCpfWrong? "CPF não encontrado" : "Digite seu CPF"} type="number" maxLength={11}  value={cpf} onChange={(e) => {if(e.target.value.length<12)setCpf(e.target.value); setIsCpfWrong(false) }} />
                        <input placeholder={isPasswordWrong ? "Senha incorreta":"Digite a sua senha" } className="senha" value={password} type="password" onChange={(e) => setPassword(e.target.value)}/>
                        <button type="button" onClick={()=> console.log('doido')}>Login</button>
                        <button type="button" onClick={()=> {setStep(3); setIsCpfWrong(false)}}>Criar nova conta</button>
                    </LoginForm>
                </LoginContainer>
                <Modal 
                    isOpen={isTransactionModalOpen}
                    overlayClassName="react-modal-overlay"
                    className="react-modal-content"
                >   
                    {createBool && (<h2>Conta criada com sucesso</h2>)}
                    {!createBool && (<h2>Conta encerrada com sucesso</h2>)}
                </Modal>
            </>
        )
    }

    if(step===3){
        return(
            <>
                <LoginContainer>
                    <SignUp isWrong={isPasswordWrong} >
                        <h2>Criar nova conta</h2>
                        <input placeholder="Digite seu Nome Completo" type="text" required name="name" onChange={()=> {setIsPasswordWrong(false); setIsCpfWrong(false)}}/>
                        <input placeholder="Digite seu CPF" type="text" maxLength={11} minLength={11} required name="cpf" onChange={()=> {setIsPasswordWrong(false); setIsCpfWrong(false)}}/>
                        <input placeholder="Digite a sua senha" type="password" name="password" required onChange={()=> {setIsPasswordWrong(false); setIsCpfWrong(false)}}/>
                        <input placeholder="Confirme a sua senha" type="password" name="password2" required onChange={()=> {setIsPasswordWrong(false); setIsCpfWrong(false)}}/>
                        <button type="submit">Enviar para análise</button>
                        <button type="button" >Voltar</button>
                    </SignUp>
                </LoginContainer>
                <Modal 
                    isOpen={isTransactionModalOpen}
                    overlayClassName="react-modal-overlay"
                    className="react-modal-content"
                >
                    <h2>Conta enviada para análise</h2>
                </Modal>
            </>
        )
    }

    return null;
}
