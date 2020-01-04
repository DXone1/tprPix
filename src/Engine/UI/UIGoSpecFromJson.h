/*
 * =================== UIGoSpecFromJson.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.12.12
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 */
#ifndef TPR_UI_GO_SPEC_FROM_JSON_H
#define TPR_UI_GO_SPEC_FROM_JSON_H
//--- glm - 0.9.9.5 ---
#include "glm_no_warnings.h"


//-------------------- CPP --------------------//
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>

//------------------- Libs --------------------//
#include "tprDataType.h" 

//-------------------- Engine --------------------//
#include "tprAssert.h"
#include "GameObjType.h" 
#include "Move.h"
#include "PubBinary2.h"



class GameObj;



class UIGoSpecFromJson{
public:
    UIGoSpecFromJson()=default; // DO NOT CALL IT DIRECTLY!!!

    std::string       goSpecName {};
    goSpecId_t        specID {};

    //----- enum -----//
    GameObjFamily     family {};

    //----- bool -----//
    //----- numbers -----//
    MoveType    moveType {};
    SpeedLevel  speedLvl {};
    //...

    //======== static ========//
    static void assemble_2_newUIGo( goSpecId_t specID_, GameObj &goRef_ );


    inline static UIGoSpecFromJson &create_new_UIGoSpecFromJson( goSpecId_t id_ ){
        auto outPair = UIGoSpecFromJson::dataUPtrs.insert({ id_, std::make_unique<UIGoSpecFromJson>() });
        tprAssert( outPair.second );
        return *(outPair.first->second);
    }

    inline static void insert_2_uiGoSpecIds_names_containers( goSpecId_t id_, const std::string &name_ ){
        auto out1 = UIGoSpecFromJson::ids_2_names.insert({ id_, name_ });
        auto out2 = UIGoSpecFromJson::names_2_ids.insert({ name_, id_ });
        tprAssert( out1.second );
        tprAssert( out2.second );
    }


    inline static goSpecId_t str_2_uiGoSpecId( const std::string &name_ ){
        tprAssert( UIGoSpecFromJson::names_2_ids.find(name_) != UIGoSpecFromJson::names_2_ids.end() );
        return UIGoSpecFromJson::names_2_ids.at(name_);
    }


    inline static const UIGoSpecFromJson &get_uiGoSpecFromJsonRef( goSpecId_t id_ ){
        tprAssert( UIGoSpecFromJson::dataUPtrs.find(id_) != UIGoSpecFromJson::dataUPtrs.end() );
        return *(UIGoSpecFromJson::dataUPtrs.at(id_));
    }


    inline static bool find_from_initFuncs( goSpecId_t goSpecId_ ){
        return (UIGoSpecFromJson::initFuncs.find(goSpecId_) != UIGoSpecFromJson::initFuncs.end());
    }


    inline static void call_initFunc(  goSpecId_t id_, GameObj &goRef_, const DyParam &dyParams_  ){
        tprAssert( UIGoSpecFromJson::find_from_initFuncs(id_) );
        UIGoSpecFromJson::initFuncs.at(id_)( goRef_, dyParams_ );
    }


    inline static void insert_2_initFuncs( const std::string &goTypeName_, const F_GO_INIT &functor_ ){
        goSpecId_t id = UIGoSpecFromJson::str_2_uiGoSpecId( goTypeName_ );
        auto outPair = UIGoSpecFromJson::initFuncs.insert({ id, functor_ });
        tprAssert( outPair.second );
    }


private:

    //======== static ========//
    // 资源持续整个游戏生命期，不用释放
    static std::unordered_map<goSpecId_t, std::unique_ptr<UIGoSpecFromJson>> dataUPtrs;
    static std::unordered_map<goSpecId_t, std::string> ids_2_names;
    static std::unordered_map<std::string, goSpecId_t> names_2_ids;
    static std::unordered_map<goSpecId_t, F_GO_INIT> initFuncs;

};



namespace json{//------------- namespace json ----------------
    void parse_uiGoJsonFile();
}//------------- namespace json: end ----------------



#endif 

