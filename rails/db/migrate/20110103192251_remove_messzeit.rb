class RemoveMesszeit < ActiveRecord::Migration
  def self.up
	change_table :measured_datas do |t|
		t.remove :messzeit
	end 
  end

  def self.down
	change_table :measured_datas do |t|
		t.column :messzeit
	end
  end   
end
