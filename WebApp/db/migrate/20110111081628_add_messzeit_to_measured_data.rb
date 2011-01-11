class AddMesszeitToMeasuredData < ActiveRecord::Migration
  def self.up
	add_column :measured_datas, :messzeit, :datetime 
  end

  def self.down
	remove_column :measured_datas, :messzeit
  end
end
